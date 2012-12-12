#include "doPrint.h"
#include "common.h"
#include <time.h>
#include <stdio.h>

void *doPrint(void *p) {
	INCLUDE(Imp)
	INCLUDE_INTEGER(PrintPaletteQueue)
	INIT_LOGGER();
	extern sem_t SemSyncBoxImp;
	extern sem_t SemPushBoxImp;
	extern int MAX_BOXES_QUEUE;

	mqd_t mboxControl = mq_open(MBOXCONTROL, O_RDWR);

	for(;;) {//@TODO Log things
		CHECK_WAIT_BOOL(Imp);
		sem_wait(&SemPushBoxImp);
		
		pthread_mutex_lock(&LockPrintPaletteQueue);
		while (PrintPaletteQueueValue >= MAX_BOXES_QUEUE) { /* We're paused */
			//* Error : The queue is full and we have to push a box to it
			SET(Imp, TRUE);// Forbidding ourself to do another loop before the green light has been set by the doControl thread
			// Sending error message (priority 2)
			int res=mq_send(mboxControl, ERR_PALETTEQUEUE, MAX_MSG_LEN, ERR_MSG_PRIORITY);
			if (res) {//* Sthing went wrong when writing to mqueue
				perror("Error while sending the error to the Control Thread");
			}
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
