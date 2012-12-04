#include "doPrint.h"
#include "common.h"
#include <time.h>

void *doPrint(void *p) {
	for(;;) {
		sleep(500 * 1000);
		printf("Printing");
	}
}
