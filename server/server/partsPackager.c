#include "semaphore.h"
#include "stdio.h"

#include "common.h"
#include "partsPackager.h"

//* @TODO : Move that to another place, later
#define DBG
#define SIMU_MODE

#ifdef SIMU_MODE
#include "time.h"

static bool simu_refusal() {
	static bool init = FALSE;

	if (!init)
	{
		init = TRUE;
		srand(NULL);
	}

	//* 30% probability to fail, 70 to succeed (if result = TRUE, then the part is REFUSED (as the function is simu_refusal()))
	bool result = ((rand() % 100) < 70) ? TRUE : FALSE; //* hey, that's C, so this is bool emulation, to shout about useless "TRUE : FALSE"
	return result;
}

#endif

void* partsPackager(void*a) {
	extern int PARTS_BY_BOX;
	extern int MAX_REFUSED_PARTS_BY_BOX;
	extern sem_t SemSyncBoxImp;
	int refusedPartsCount = 0;//* Number of parts that have been refused for the current box (not to be higher than MAX_REFUSED_PARTS_BY_BOX)
	
	int currentBoxPartsNumber = 0;
	//**** INIT
	
#ifdef DBG
	printf("%d\n", (int)getpid());
#endif

	//**** MAIN LOOP
	for (;;) {
		sem_wait(SemCtrlBox);

		bool refused = TRUE;
#ifdef SIMU_MODE
		refused = simu_refusal();
#endif
	if (!refused) //* Part is accepted
	{
		//* There's a new part to put in that freaking box:
		currentBoxPartsNumber = (currentBoxPartsNumber + 1) % PARTS_BY_BOX;

		if (!currentBoxPartsNumber) //* Is the box full?
		{
			refusedPartsCount = 0; //* Reset refused parts by box counter

			//**** "READY TO GO TO PRINTER" SEMAPHORE CHECK
			sem_wait(&SemSyncBoxImp);
		}
		//* At the end of the loop, we are basically just waiting for a new part
		//* This part will come as a signal (supposed to be an IT)
		//* Thus in order to wait for it, we just pause ourself:
	} else {
		refusedPartsCount++;
		if (refusedPartsCount >= MAX_REFUSED_PARTS_BY_BOX)
		{
			//* @TODO Error case: parts refused rate reached for the current box
		}
	}

	pause();
}


	//**** END / CLEANING 
}
