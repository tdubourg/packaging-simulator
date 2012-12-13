#include "semaphore.h"
#include "stdio.h"
#include "errno.h"

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

static bool simu_missing_box() {
	bool missing = TRUE;
	FILE * fileMissingBox = fopen(SIMU_BOX_FILE_NAME, "rb");

	if (fileMissingBox == NULL) { // If the file is not found, it means that the box is here
		if(errno == ENOENT) {
			missing = FALSE;
		}
	} else {
		fclose(fileMissingBox);
	}
	return missing;
}

#endif

void* partsPackager(void*a) {
	//**** INIT
	INCLUDE(Box)
	INCLUDE(Valve)
	INIT_LOGGER();
	INIT_CONTROL();
	extern int PARTS_BY_BOX;
	extern int MAX_REFUSED_PARTS_BY_BOX;
	extern sem_t SemSyncBoxImp;
	extern sem_t SemPushBoxImp;
	extern sem_t SemNewPart;
	int refusedPartsCount = 0;//* Number of parts that have been refused for the current box (not to be higher than MAX_REFUSED_PARTS_BY_BOX)
	int currentBoxPartsNumber = 0;

#ifdef DBG
	printf("%d\n", (int) getpid());
#endif

	//**** MAIN LOOP
	for (;;) {
		CHECK_WAIT_BOOL(Box);
		CHECK_FOR_APP_END_AND_STOP(Box);
		DBG("partsPackager", "Main", "Task is unlocked.");
		
		bool missing = TRUE;
#ifdef SIMU_MODE
		missing = simu_missing_box();
#endif
		
		if(missing) {
			//* Closing the valve
				SET(Valve, TRUE);
				DBG("doControl", "Main", "Closing valve.");
				LOG("partsPackager: Missing box, ERROR.");
				SET(Box, TRUE);// Forbidding ourself to do another loop before the green light has been set by the doControl thread
				
				// Sending error message
				ERR_MSG(ERR_BOX);
				// Going back to the beginning of the loop and standing still until the doControl thread says otherwise
				continue;
		}
		
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
			LOG("partsPackager: New accepted part.");
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
			LOG("partsPackager: New REFUSED part.");

			refusedPartsCount++;
			if (refusedPartsCount >= MAX_REFUSED_PARTS_BY_BOX)
			{
				//* Closing the valve
				SET(Valve, TRUE);
				DBG("doControl", "Main", "Closing valve.");
				LOG("partsPackager: Refused rate is too high, ERROR.");
				SET(Box, TRUE);// Forbidding ourself to do another loop before the green light has been set by the doControl thread
				
				// Sending error message
				ERR_MSG(ERR_BOX_REFUSED_RATE);
			}
		}
	}
	//**** END / CLEANING 
}
