#include "semaphore.h"
#include "stdio.h"

#include "common.h"
#include "partsPackager.h"

//* @TODO : Move that to another place, later

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
	bool result = ((rand() % 100) < 70) ? FALSE : TRUE; //* hey, that's C, so this is bool emulation, to shout about useless "TRUE : FALSE"
	return result;
}

#endif

void* partsPackager(void*a) {
	int refusedPartsCount = 0;//* Number of parts that have been refused for the current box (not to be higher than MAX_REFUSED_PARTS_BY_BOX)
	
	int currentBoxPartsNumber = 0;
	//**** INIT
	// Opening message queue
	mqd_t mboxControl = mq_open(MBOXCONTROL, O_RDWR);
#ifdef DBG
	printf("%d\n", (int)getpid());
#endif

	//**** MAIN LOOP
	for (;;) {
		// sem_wait(&SemCtrlBox);
		pthread_mutex_unlock(&LockBox);
		while(!LockBoxValue) { /* We're paused */
			pthread_cond_wait(&CondBox, &LockBox); /* Wait for play signal */
		}
		pthread_mutex_unlock(&LockBox);
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
		//* At the end of the loop, we are basically just waiting for a new part
		//* This part will come as a signal (supposed to be an IT)
		//* Thus in order to wait for it, we just pause ourself:
	} else {
		DBG("partsPackager", "Main", "New REFUSED part.");
		refusedPartsCount++;
		if (refusedPartsCount >= MAX_REFUSED_PARTS_BY_BOX)
		{
			//* @TODO Error case: parts refused rate reached for the current box

						// Sending error message (priority 2)
						//* @TODO : replace message with correct format
			int res=mq_send(mboxControl, "E Error refused parts rate", MAX_MSG_LEN, 2);
			refusedPartsCount = 0;
			if (res)
			{
				perror("Error while sending the error to the Control Thread");
			}
		}
	}
}


	//**** END / CLEANING 
}
