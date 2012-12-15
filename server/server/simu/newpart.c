#include "newpart.h"
#include "../common.h"

extern sem_t SemNewPart;

void *newpart(void* a) {
	INCLUDE(Valve)

	for(;;) {
		CHECK_WAIT_BOOL(Valve);
		DBGPRINT("newpart", "Main", "Pushing new part");
		sem_post(&SemNewPart);
		usleep(200 * 1000);
	}
}
