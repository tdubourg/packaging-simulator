#include "doPrint.h"
#include "common.h"
#include <time.h>
#include <stdio.h>

void *doPrint(void *p) {
	extern sem_t SemSyncBoxImp;
	extern sem_t SemPushBoxImp;
	INCLUDE(Palette)
	extern int BOXES_QUEUE;
	extern int MAX_BOXES_QUEUE;

	for(;;) {
		sem_wait(&SemPushBoxImp);
		
		pthread_mutex_lock(&LockPalette);
		while (BOXES_QUEUE >= MAX_BOXES_QUEUE) { /* We're paused */
			pthread_cond_wait(&CondPalette, &LockPalette); /* Wait for play signal */
		}
		DBG("doPrint", "Main", "Printing");
        ++BOXES_QUEUE;
		pthread_cond_signal(&CondPalette);
		DBG("doPrint", "Main", "New box in the queue");
		pthread_mutex_unlock(&LockPalette);
		
		sem_post(&SemSyncBoxImp);
	}
}
