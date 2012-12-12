#include "doPalette.h"
#include "common.h"

void *doPalette(void *p)
{
	//**** INIT
	INCLUDE(Palette)
	INCLUDE_INTEGER(PrintPaletteQueue)
	INIT_LOGGER();
	INIT_CONTROL();
	extern int BOXES_BY_PALETTE;
	extern sem_t SemSyncImpPalette;
	int currentPaletteBoxesNumber = 0;
	
	//***** MAIN LOOP
	for(;;) {
		CHECK_WAIT_BOOL(Palette);
		sem_wait(&SemSyncImpPalette);
		pthread_mutex_lock(&LockPrintPaletteQueue);
		//@TODO Here check that there actually is a palette (sensor simulation)
		// and in case of error : ERR_MSG()...
		while (PrintPaletteQueueValue <= 0) { /* We're paused */
			DBG("doPalette", "Main", "Queue is empty. Nothing to do.");
			LOG("doPalette: Queue is empty. Nothing to do.");
			pthread_cond_wait(&CondPrintPaletteQueue, &LockPrintPaletteQueue); /* Wait for play signal */
		}
		DBG("doPalette", "Main", "New box added in palette");
		LOG("doPalette: New box added in current palette");
		--PrintPaletteQueueValue;
		currentPaletteBoxesNumber = (currentPaletteBoxesNumber + 1) % BOXES_BY_PALETTE;
		pthread_cond_signal(&CondPrintPaletteQueue);
		pthread_mutex_unlock(&LockPrintPaletteQueue);
		sem_post(&SemSyncImpPalette);
	}
}