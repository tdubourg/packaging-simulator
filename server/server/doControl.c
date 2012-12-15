#include "doControl.h"
#include "common.h"
#include "string.h"
#include "stdlib.h"

#ifdef DBG
#include "time.h"
#include "stdio.h"
#endif

static void stopApplication();
static void parseInitMessage(char* buffer);

/*
 * Control thread
 */
void *doControl(void *p) {
	INCLUDE(Imp)
	INCLUDE(Palette)
	INCLUDE(Valve)
	INCLUDE(Box)
	INIT_LOGGER();

	char msg[MAX_MSG_LEN + 1];
	mqd_t mboxControl = mq_open(MBOXCONTROL, O_RDWR);

	for (;;)
	{
		/* Wait for a command */
		mq_receive(mboxControl, msg, MAX_MSG_LEN, NULL);
		DBGPRINT("doControl", "Main", "Received a message");
		DBGPRINT("doControl", "Main", msg);
		switch (msg[0])
		{
			/* Error case */
			case ERR:
			{
				/* Stop the valve */
				char* errMsg = (char*)malloc(strlen(ERR_LOG_PREFIX) + 2);
				errMsg[0] = '\0';
				strcat(errMsg, ERR_LOG_PREFIX);
				strcat(errMsg, msg+1 /* skip the first char of the char[] */);
				LOG_ERR(errMsg);
				SET(Valve, TRUE);
				switch (msg[1])
				{
					/* Print */
					case PRINT:
						/* Block parts packager */
						SET(Box, TRUE);
						break;
					/* Palette maker : palette is not here */
					case PALETTE:
						/* Block print */
						SET(Palette, TRUE);
						break;
					/* Palette maker : queue is full */
					case PALETTE_QUEUE:
						/* Block print */
						SET(Imp, TRUE);
						break;
					/* Warehouse */
					case WAREHOUSE:
						/* Block palette maker */
						SET(Palette, TRUE);
						break;
					/* Box maker : the refused rate is too high */
					case BOX_REFUSED_RATE:
						/* Block box maker */
						SET(Box, TRUE);
						break;
				}
				free(errMsg);
			}
				break;
			/* Solving errors */
			/* Relaunch all tasks (tasks that were not blocked will not see anything) */
			case SOLVE:
				SET(Box, FALSE);
				SET(Palette, FALSE);
				SET(Imp, FALSE);
				SET(Valve, FALSE);
				break;
			/* Stop app */
			case 'Q':
				SET(Valve, TRUE);
				stopApplication();
				//stopping this thread;
				return;
			case 'I':
				parseInitMessage(msg);
				break;
		}
	}
}

static void parseInitMessage(char* buffer) {
	char* token, errorMsg;
	char *saveptr1;
	batch_type batchType;
	int nbRefusedPart, partByBox, boxByPallet, nbPallet;
	extern batch_type CurrentBatchType;
	extern int CurrentBatchProdMax;
	extern int PARTS_BY_BOX;
	extern int BOXES_BY_PALETTE;
	extern int MAX_REFUSED_PARTS_BY_BOX;
	extern int CurrentProducedBoxes;
	extern int CurrentBatchRefusedPartsNumber;

	INCLUDE(Imp)
	INCLUDE(Palette)
	INCLUDE(Valve)
	INCLUDE(Box)
	INIT_LOGGER();

	
	// reading init
	token = strtok_r(buffer, "-", &saveptr1);
	if (token == NULL || strcmp(token, INIT_BATCH)) {
//		errorMsg = "Bad batch initialisation message : ";
//		strcat(errorMsg, buffer);
		LOG("Bad batch initialisation message : message not starting with INIT");
		return;
	}

	//reading batch type
	token = strtok_r(NULL, "-", &saveptr1);
	if (token == NULL || (strcmp(token, "A") && strcmp(token, "B"))) {
//		errorMsg = "Bad batch initialisation message : ";
//		strcat(errorMsg, buffer);
		LOG("Bad batch initialisation message : batch type isn't \"a\" or \"b\"");
		return;
	}
	if (!strcmp(token, "A")) {
		batchType = BATCH_TYPE_A;
	}
	if (!strcmp(token, "B")) {
		batchType = BATCH_TYPE_B;
	}

	// reading refused part
	token = strtok_r(NULL, "-", &saveptr1);
	if (token == NULL && (nbRefusedPart = atoi(token))!=0) {
//		errorMsg = "Bad batch initialisation message : ";
//		strcat(errorMsg, buffer);
		LOG("Bad batch initialisation message : missing/malformated refused part number");
		return;
	}
	nbRefusedPart = atoi(token);

	// reading part by box
	token = strtok_r(NULL, "-", &saveptr1);
	if (token == NULL) {
//		errorMsg = "Bad batch initialisation message : ";
//		strcat(errorMsg, buffer);
		LOG("Bad batch initialisation message");
		return;
	}
	partByBox = atoi(token);

	// reading box by pallet
	token = strtok_r(NULL, "-", &saveptr1);
	if (token == NULL) {
//		errorMsg = "Bad batch initialisation message : ";
//		strcat(errorMsg, buffer);
		LOG("Bad batch initialisation message");
		return;
	}
	boxByPallet = atoi(token);

	// reading number of pallet
	token = strtok_r(NULL, "-", &saveptr1);
	if (token == NULL) {
//		errorMsg = "Bad batch initialisation message : ";
//		strcat(errorMsg, buffer);
		LOG("Bad batch initialisation message");
		return;
	}
	nbPallet = atoi(token);

	// if parsing was successfull we initialise batch
	CurrentBatchType = batchType;
	CurrentBatchProdMax = nbPallet;
	PARTS_BY_BOX = partByBox;
	BOXES_BY_PALETTE = boxByPallet;
	MAX_REFUSED_PARTS_BY_BOX = nbRefusedPart;
	//initializing compters
	CurrentProducedBoxes = 0;
	CurrentBatchRefusedPartsNumber=0;
	// starting production
	SET(Box, FALSE);
	SET(Palette, FALSE);
	SET(Imp, FALSE);
	SET(Valve, FALSE);

}

static void stopApplication() {
	// stopping simulation threads
	extern bool needToStop;
	INCLUDE(Box);
	INCLUDE(Imp);
	INCLUDE(Palette);
	INCLUDE(Valve);
	extern sem_t SemSyncBoxImp;
	extern sem_t SemPushBoxImp;
	extern sem_t SemSyncImpPalette;
	extern sem_t SemNewPart;
	extern sem_t SemWarehouse;
	mqd_t mboxPalletStore = mq_open(MBOXPALLETSTORE, O_RDWR);
	mqd_t mboxLogs = mq_open(MBOXLOGS, O_RDWR);
	mqd_t mboxCom = mq_open(MBOXCOMMUNICATION, O_RDWR);
	needToStop = TRUE;

	mq_send(mboxPalletStore, STOP_MESSAGE_QUEUE, sizeof (STOP_MESSAGE_QUEUE), MSG_LOW_PRIORITY);

	// waiting for simulation threads to end
	SET(Valve, FALSE);
	sleep(1);
	
	// Unlocking other tasks
	//* Warehouse...
	sem_post(&SemWarehouse);
	//* Pallet...
	sem_post(&SemSyncImpPalette);
	SET(Palette, FALSE);
	//* Printer...
	sem_post(&SemPushBoxImp);
	SET(Imp, FALSE);
	//* Parts packager...
	sem_post(&SemSyncBoxImp);
	sem_post(&SemNewPart);
	SET(Box, FALSE);

	// closing Log thread;
	mq_send(mboxLogs, STOP_MESSAGE_QUEUE, sizeof (STOP_MESSAGE_QUEUE), MSG_LOW_PRIORITY);

	//* Note : No need to terminate doCommunication as it terminates by itself on shutdown order.
	
	
}
