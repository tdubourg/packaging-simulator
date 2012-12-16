#include "newpart.h"
#include "../common.h"

extern sem_t SemNewPart;

void *newpart(void* a) {
	INCLUDE(Valve)

	for (;;) {
		CHECK_WAIT_BOOL(Valve);
		CHECK_FOR_APP_END_AND_STOP("Valve");
		DBGPRINT("newpart", "Main", "Pushing new part");
		sem_post(&SemNewPart);
		usleep(200 * 1000);
	}
}
