#include "semaphore.h"
#include "stdio.h"
#include "errno.h"
#include "time.h"

#include "common.h"
#include "doBox.h"

#ifdef SIMU_MODE
static bool simu_refusal();
static bool simu_missing_box();
#endif

void* doBox(void*a) {
	/* **** INIT */
	INCLUDE(Box)
	INCLUDE(Valve)
	INIT_LOGGER();
	INIT_CONTROL();
	INIT_CHECK_FOR_APP_END();
	extern int PARTS_BY_BOX;
	extern int MAX_REFUSED_PARTS_BY_BOX;
	extern int CurrentBatchProdMax;
	extern int CurrentProducedBoxes;
	extern int CurrentBatchRefusedPartsNumber;
	extern int BOXES_BY_PALETTE;
	extern sem_t SemSyncBoxPrint;
	extern sem_t SemPushBoxPrint;
	extern sem_t SemNewPart;
	int refusedPartsCount = 0;/* Number of parts that have been refused for the current box (not to be higher than MAX_REFUSED_PARTS_BY_BOX) */
	int currentBoxPartsNumber = 0;

#ifdef DBG
	printf("%d\n", (int) getpid());
#endif

	/* **** MAIN LOOP */
	for (;;) {
		CHECK_WAIT_BOOL(Box);
		CHECK_FOR_APP_END_AND_STOP("Box");
		DBGPRINT("doBox", "Main", "Task is unlocked.");
		
		bool boxIsMissing = TRUE;
#ifdef SIMU_MODE
		boxIsMissing = simu_missing_box();
#endif
		
		if(boxIsMissing) {
			/* Closing the valve */
			LOCK(Valve);
			DBGPRINT("doBox", "Main", "Closing valve.");
			LOG("doBox: Missing box, ERROR.");
			LOCK(Box);/* Forbidding ourself to do another loop before the green light has been set by the doControl thread */
			
			/* Sending error message */
			ERR_MSG(ERR_BOX);
			/* Going back to the beginning of the loop and standing still until the doControl thread says otherwise */
			continue;
		}
		
		/* At the end of the loop (and thus at its beginning, the other way around), we are basically just waiting for a new part
		   This part will come as a unlocking the sempahore SemSimuNewPart (supposed to be an IT) */
		sem_wait(&SemNewPart);

		bool refused = TRUE;
#ifdef SIMU_MODE
		refused = simu_refusal();
#endif
		if (!refused) /* Part is accepted */
		{
			DBGPRINT("doBox", "Main", "New accepted part.");
			LOG("doBox: New accepted part.");
			/* There's a new part to put in that freaking box: */
			currentBoxPartsNumber = (currentBoxPartsNumber + 1) % PARTS_BY_BOX;
			DBGPRINT("doBox", "Main", "currentBoxPartsNumber=");
#ifdef DBG
			printf("%d\n", currentBoxPartsNumber);
#endif

			if (!currentBoxPartsNumber) /* Is the box full? */
			{
				DBGPRINT("doBox", "Main", "The box is full");
				refusedPartsCount = 0; /* Reset refused parts by box counter */
				CurrentProducedBoxes++;
				if ((CurrentProducedBoxes / BOXES_BY_PALETTE) >= CurrentBatchProdMax)
				{
					/* The current batch is over, so close the valve */
					LOCK(Valve);
					LOG("GAME OVER");
				}
				/* **** "READY TO GO TO PRINTER" SEMAPHORE CHECK */
				sem_wait(&SemSyncBoxPrint);
				sem_post(&SemPushBoxPrint);
			}
		} else {
			DBGPRINT("doBox", "Main", "New REFUSED part.");
			LOG("doBox: New REFUSED part.");

			refusedPartsCount++;
			CurrentBatchRefusedPartsNumber++;
			if (refusedPartsCount >= MAX_REFUSED_PARTS_BY_BOX)
			{
				/* Closing the valve */
				refusedPartsCount = 0; /* Resetting the counter, so that when the error is marked as "solved" we don't go back into error mode */
				LOCK(Valve);
				DBGPRINT("doBox", "Main", "Closing valve.");
				LOG("doBox: Refused rate is too high, ERROR.");
				LOCK(Box);/* Forbidding ourself to do another loop before the green light has been set by the doControl thread */
				
				/* Sending error message */
				ERR_MSG(ERR_BOX_REFUSED_RATE);
			}
		}
	}
	/* **** END / CLEANING */
}

#ifdef SIMU_MODE
static bool simu_refusal() {
	
	static bool init = FALSE;
	int rate;
	
	if(!init) {
		init = TRUE;
		srand(1024);
	}
	FILE * fileRefusalRate = fopen(REFUSAL_RATE_FILE_NAME, "rb");
	if (fileRefusalRate == NULL) { /* By default, refusal rate = 30% */
		rate = 30;
	} else {
		char read[4];
		fgets(read, sizeof(read), fileRefusalRate);
		fclose(fileRefusalRate);
		rate = atoi(read) % 100;
	}
#ifdef DBG
	printf("Refusal rate : %d\n", rate);
#endif
	/* "rate" probability to fail, 100-"rate" to succeed (if result = TRUE, then the part is REFUSED (as the function is simu_refusal())) */
	return (rand() % 100) < rate;
}

static bool simu_missing_box() {
	bool missing = TRUE;
	FILE * fileMissingBox = fopen(SIMU_BOX_FILE_NAME, "rb");

	if (fileMissingBox == NULL) { /* If the file is not found, it means that the box is there */
		if(errno == ENOENT) {
			missing = FALSE;
		}
	} else {
		fclose(fileMissingBox);
	}
	return missing;
}
#endif
