#include "doPrint.h"
#include "common.h"
#include <time.h>
#include <stdio.h>

void *doPrint(void *p) {
	INCLUDE(Print)
	INCLUDE_INTEGER(PrintPaletteQueue)
	extern sem_t SemSyncBoxImp;
	extern sem_t SemPushBoxImp;
	extern int MAX_BOXES_QUEUE;

	for(;;) {
		sem_wait(&SemPushBoxImp);
		
		pthread_mutex_lock(&LockPrintPaletteQueue);
		while (PrintPaletteQueueValue >= MAX_BOXES_QUEUE) { /* We're paused */
			pthread_cond_wait(&CondPrintPaletteQueue, &LockPrintPaletteQueue); /* Wait for play signal */
		}
		DBG("doPrint", "Main", "Printing");
        PrintPaletteQueueValue++;
		pthread_cond_signal(&CondPrintPaletteQueue);
		DBG("doPrint", "Main", "New box in the queue");
		pthread_mutex_unlock(&LockPrintPaletteQueue);
		sem_post(&SemSyncBoxImp);
	}
}
