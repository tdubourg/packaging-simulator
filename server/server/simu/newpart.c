#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include "semaphore.h"

#include "newpart.h"

sem_t SemNewPart;

void *newpart(void* a) {
	extern pthread_cond_t CondValve;
	extern pthread_mutex_t LockValve;
	extern bool LockValveValue;

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

// int main(int argc, char const *argv[])
// {
// 	int pid = -1;
// 	if (argc > 1)
// 	{
// 		pid = atoi(argv[1]);
// 	}

// 	newpart((-1 != pid) ? &pid : NULL);
// 	return 0;
// }