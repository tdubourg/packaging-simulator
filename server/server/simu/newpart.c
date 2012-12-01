#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

#include "newpart.h"

void newpart(void* a) {
	for(;;) {
		printf("Pouet\n");
		usleep(500 * 1000);
		if (NULL != a)
		{
			pid_t* pid = (pid_t*)a;
			kill(*pid, SIGUSR2);
		}
	}
}

int main(int argc, char const *argv[])
{
	int pid = -1;
	if (argc > 1)
	{
		pid = atoi(argv[1]);
	}

	newpart((-1 != pid) ? &pid : NULL);
	return 0;
}
