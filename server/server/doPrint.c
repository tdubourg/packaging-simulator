#include "doPrint.h"
#include "common.h"
#include <time.h>
#include <stdio.h>

void *doPrint(void *p) {
	INCLUDE(Print)
	extern sem_t SemSyncBoxImp;
	extern sem_t SemPushBoxImp;
	extern pthread_mutex_t paletteLock;
	extern pthread_cond_t paletteCond;
	extern int BoxesQueue;
	extern int MAX_BOXES_QUEUE;

	for(;;) {
		sem_wait(&SemPushBoxImp);
		
		pthread_mutex_lock(&paletteLock);
		while (BoxesQueue >= MAX_BOXES_QUEUE) { /* We're paused */
			pthread_cond_wait(&paletteCond, &paletteLock); /* Wait for play signal */
		}
		DBG("doPrint", "Main", "Printing");
        BoxesQueue++;
		pthread_cond_signal(&paletteCond);
		DBG("doPrint", "Main", "New box in the queue");
		pthread_mutex_unlock(&paletteLock);
		
		sem_post(&SemSyncBoxImp);
	}
}
