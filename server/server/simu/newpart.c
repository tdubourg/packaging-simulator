#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include "semaphore.h"

#include "newpart.h"

sem_t SemNewPart;

void newpart(void* a) {
	for(;;) {
		printf("Pouet\n");
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
