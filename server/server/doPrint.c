#include "doPrint.h"
#include "common.h"
#include <time.h>
#include <stdio.h>
#include <errno.h>

#ifdef SIMU_MODE

static bool simu_printer_error() {
	bool printerError = TRUE;
	FILE * filePrinterError = fopen(SIMU_PRINT_FILE_NAME, "rb");

	if (filePrinterError == NULL) { // If the file is not found, it means that the printer works correctly
		if(errno == ENOENT) {
			printerError = FALSE;
		}
	} else {
		fclose(filePrinterError);
	}
	return printerError;
}

#endif


void *doPrint(void *p) {
	INCLUDE(Imp)
	INCLUDE(Valve)
	INCLUDE_INTEGER(PrintPaletteQueue)
	INIT_LOGGER();
	INIT_CONTROL();
	INIT_CHECK_FOR_APP_END();
	extern sem_t SemSyncBoxImp;
	extern sem_t SemPushBoxImp;
	extern int MAX_BOXES_QUEUE;
	for(;;) {
		CHECK_WAIT_BOOL(Imp);
		CHECK_FOR_APP_END_AND_STOP("Imp");
		bool printerError = TRUE;

#ifdef SIMU_MODE
		printerError = simu_printer_error();
#endif
		if(printerError) {
			//* Closing the valve
			SET(Valve, TRUE);
			DBG("doPrint", "Main", "Closing valve.");
			LOG("doPrint: Printer error, ERROR.");
			SET(Imp, TRUE);// Forbidding ourself to do another loop before the green light has been set by the doControl thread
				
			// Sending error message
			ERR_MSG(ERR_PRINT);
			// Going back to the beginning of the loop and standing still until the doControl thread says otherwise
			continue;
		}
		sem_wait(&SemPushBoxImp);
		
		pthread_mutex_lock(&LockPrintPaletteQueue);
		while (PrintPaletteQueueValue >= MAX_BOXES_QUEUE) { /* We're paused */
			//* Error : The queue is full and we have to push a box to it
			SET(Imp, TRUE);// Forbidding ourself to do another loop before the green light has been set by the doControl thread
			// Sending error message (priority 2)
			ERR_MSG(ERR_PALETTE_QUEUE);
			pthread_cond_wait(&CondPrintPaletteQueue, &LockPrintPaletteQueue); /* Wait for play signal */
		}
		DBG("doPrint", "Main", "Printing");
		LOG("doPrint: Printing.");
        PrintPaletteQueueValue++;
		pthread_cond_signal(&CondPrintPaletteQueue);
		DBG("doPrint", "Main", "Pushing a new box to the doPalette queue");
		LOG("doPrint: Pushing a new box to the doPalette queue");
		pthread_mutex_unlock(&LockPrintPaletteQueue);
		sem_post(&SemSyncBoxImp);
	}
}
