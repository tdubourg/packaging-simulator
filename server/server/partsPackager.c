#include "semaphore.h"
#include "stdio.h"

#include "common.h"
#include "partsPackager.h"

//* @TODO : Move that to another place, later

#ifdef SIMU_MODE
#include "time.h"

static bool simu_refusal() {
	static bool init = FALSE;

	if (!init) {
		init = TRUE;
		srand(1024);
	}

	//* 30% probability to fail, 70 to succeed (if result = TRUE, then the part is REFUSED (as the function is simu_refusal()))
	return (rand() % 100) < 30;
}

#endif

void* partsPackager(void*a) {
	//**** INIT
	INCLUDE(Box)
	INCLUDE(Valve)
	extern int PARTS_BY_BOX;
	extern int MAX_REFUSED_PARTS_BY_BOX;
	extern sem_t SemSyncBoxImp;
	extern sem_t SemPushBoxImp;
	extern sem_t SemNewPart;
	int refusedPartsCount = 0;//* Number of parts that have been refused for the current box (not to be higher than MAX_REFUSED_PARTS_BY_BOX)
	int currentBoxPartsNumber = 0;
	// Opening message queue
	mqd_t mboxControl = mq_open(MBOXCONTROL, O_RDWR);

#ifdef DBG
	printf("%d\n", (int) getpid());
#endif

	//**** MAIN LOOP
	for (;;) {//@TODO Log things

		CHECK_WAIT_BOOL(Box);

		//* At the end of the loop (and thus at its beginning, the other way around), we are basically just waiting for a new part
		//* This part will come as a unlocking the sempahore SemSimuNewPart (supposed to be an IT)
		sem_wait(&SemNewPart);

		bool refused = TRUE;
#ifdef SIMU_MODE
		refused = simu_refusal();
#endif
		if (!refused) //* Part is accepted
		{
			DBG("partsPackager", "Main", "New accepted part.");
			//* There's a new part to put in that freaking box:
			currentBoxPartsNumber = (currentBoxPartsNumber + 1) % PARTS_BY_BOX;
			DBG("partsPackager", "Main", "currentBoxPartsNumber=");
#ifdef DBG
			printf("%d\n", currentBoxPartsNumber);
#endif

			if (!currentBoxPartsNumber) //* Is the box full?
			{
				DBG("partsPackager", "Main", "The box is full");
				refusedPartsCount = 0; //* Reset refused parts by box counter

				//**** "READY TO GO TO PRINTER" SEMAPHORE CHECK
				sem_wait(&SemSyncBoxImp);
				sem_post(&SemPushBoxImp);
			}
		} else {
			DBG("partsPackager", "Main", "New REFUSED part.");
			refusedPartsCount++;
			if (refusedPartsCount >= MAX_REFUSED_PARTS_BY_BOX)
			{
				//* Closing the valve
				SET(Valve, TRUE);
				DBG("doControl", "Main", "Closing valve.");
				SET(Box, TRUE);// Forbidding ourself to do another loop before the green light has been set by the doControl thread
				
				// Sending error message (priority 2)
				int res=mq_send(mboxControl, ERR_BOX_REFUSED_RATE, MAX_MSG_LEN, 2);
				refusedPartsCount = 0;
				if (res) {
					perror("Error while sending the error to the Control Thread");
				}
			}
		}
	}
	//**** END / CLEANING 
}
