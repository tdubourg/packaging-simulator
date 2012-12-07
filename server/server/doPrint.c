#include "doPrint.h"
#include "common.h"
#include <time.h>
#include <stdio.h>

void *doPrint(void *p) {
	extern sem_t SemSyncBoxImp;
	extern sem_t SemPushBoxImp;
	for(;;) {
		sem_wait(&SemPushBoxImp);
		DBG("doPrint", "Main", "Printing");
		sem_post(&SemSyncBoxImp);
	}
}
