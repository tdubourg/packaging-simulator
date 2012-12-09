#include "newpart.h"
#include "../common.h"

extern sem_t SemNewPart;

void *newpart(void* a) {
	INCLUDE(Valve)

	for(;;) {
		pthread_mutex_lock(&LockValve);
		while(!LockValveValue) { /* We're paused */
			pthread_cond_wait(&CondValve, &LockValve); /* Wait for play signal */
		}
		pthread_mutex_unlock(&LockValve);
		DBG("newpart", "Main", "Pushing new part");
		sem_post(&SemNewPart);
		usleep(500 * 1000);
	}
}
