#include "newpart.h"
#include "../common.h"

extern sem_t SemNewPart;

void *newpart(void* a) {
	for(;;) {
		usleep(500 * 1000);
		sem_post(&SemNewPart);
	}
}
