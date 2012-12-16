#include "doControl.h"
#include "common.h"
#include "string.h"
#include "stdlib.h"

#ifdef DBG
#include "time.h"
#include "stdio.h"
#endif

static void parseInitMessage(char* buffer);
static void stopApplication();

/*
 * Control thread
 */
void *doControl(void *p) {
	INCLUDE(Print)
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
				/* Stop the valve on error */
				LOCK(Valve);
				/* Then log the error such a way that the network client can parse it easily (prefix + error) */
				char* errMsg = (char*)malloc(strlen(ERR_LOG_PREFIX) + 2);
				errMsg[0] = '\0';
				strcat(errMsg, ERR_LOG_PREFIX);
				strcat(errMsg, msg+1 /* skip the first char of the char[] */);
				/* Error msg is now ready to be logged : (memory freeing is done after the switch) */ 
				LOG_ERR(errMsg);

				switch (msg[1])
				{
					/* Print */
					case PRINT:
						/* Block parts packager */
						LOCK(Box);
						break;
					/* Palette maker : palette is not here */
					case PALETTE:
						/* Block print */
						LOCK(Palette);
						break;
					/* Palette maker : queue is full */
					case PALETTE_QUEUE:
						/* Block print */
						LOCK(Print);
						break;
					/* Warehouse */
					case WAREHOUSE:
						/* Block palette maker */
						LOCK(Palette);
						break;
					/* Box maker : the refused rate is too high */
					case BOX_REFUSED_RATE:
						/* Block box maker */
						LOCK(Box);
						break;
				}
				/* Release error message dynamically allocated memory */
				free(errMsg);
			}
				break;
			/* Solving errors */
			/* Relaunch all tasks (tasks that were not blocked will not see anything) */
			case SOLVE:
				UNLOCK(Box);
				UNLOCK(Palette);
				UNLOCK(Print);
				UNLOCK(Valve);
				break;
			/* Stop app */
			case 'Q':
				LOCK(Valve);
				stopApplication();
				/* Stopping this thread */
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

	INCLUDE(Print)
	INCLUDE(Palette)
	INCLUDE(Valve)
	INCLUDE(Box)
	INIT_LOGGER();

	
	/* Reading init */
	token = strtok_r(buffer, "-", &saveptr1);
	if (token == NULL || strcmp(token, INIT_BATCH)) {
		/* errorMsg = "Bad batch initialisation message : ";
		strcat(errorMsg, buffer); */
		LOG("Bad batch initialisation message : message not starting with INIT");
		return;
	}

	/* Reading batch type */
	token = strtok_r(NULL, "-", &saveptr1);
	if (token == NULL || (strcmp(token, "A") && strcmp(token, "B"))) {
		/* errorMsg = "Bad batch initialisation message : ";
		strcat(errorMsg, buffer); */
		LOG("Bad batch initialisation message : batch type isn't \"a\" or \"b\"");
		return;
	}
	if (!strcmp(token, "A")) {
		batchType = BATCH_TYPE_A;
	}
	if (!strcmp(token, "B")) {
		batchType = BATCH_TYPE_B;
	}

	/* Reading refused part */
	token = strtok_r(NULL, "-", &saveptr1);
	if (token == NULL && (nbRefusedPart = atoi(token))!=0) {
		/* errorMsg = "Bad batch initialisation message : ";
		strcat(errorMsg, buffer); */
		LOG("Bad batch initialisation message : missing/malformated refused part number");
		return;
	}
	nbRefusedPart = atoi(token);

	/* Reading part by box */
	token = strtok_r(NULL, "-", &saveptr1);
	if (token == NULL) {
		/* errorMsg = "Bad batch initialisation message : ";
		strcat(errorMsg, buffer); */
		LOG("Bad batch initialisation message");
		return;
	}
	partByBox = atoi(token);

	/* Reading box by pallet */
	token = strtok_r(NULL, "-", &saveptr1);
	if (token == NULL) {
		/* errorMsg = "Bad batch initialisation message : ";
		strcat(errorMsg, buffer); */
		LOG("Bad batch initialisation message");
		return;
	}
	boxByPallet = atoi(token);

	/* Reading number of pallets */
	token = strtok_r(NULL, "-", &saveptr1);
	if (token == NULL) {
		/* errorMsg = "Bad batch initialisation message : ";
		strcat(errorMsg, buffer); */
		LOG("Bad batch initialisation message");
		return;
	}
	nbPallet = atoi(token);

	/* If parsing was successful, we initialize batch */
	CurrentBatchType = batchType;
	CurrentBatchProdMax = nbPallet;
	PARTS_BY_BOX = partByBox;
	BOXES_BY_PALETTE = boxByPallet;
	MAX_REFUSED_PARTS_BY_BOX = nbRefusedPart;
	/* Initializing compters */
	CurrentProducedBoxes = 0;
	CurrentBatchRefusedPartsNumber=0;
	/* Starting production */
	UNLOCK(Box);
	UNLOCK(Palette);
	UNLOCK(Print);
	UNLOCK(Valve);
}

static void stopApplication() {
	/* Stopping simulation threads */
	extern bool needToStop;
	INCLUDE(Box);
	INCLUDE(Print);
	INCLUDE(Palette);
	INCLUDE(Valve);
	extern sem_t SemSyncBoxPrint;
	extern sem_t SemPushBoxPrint;
	extern sem_t SemSyncPrintPalette;
	extern sem_t SemNewPart;
	extern sem_t SemWarehouse;
	mqd_t mboxPalletStore = mq_open(MBOXPALLETSTORE, O_RDWR | O_NONBLOCK);
	mqd_t mboxLogs = mq_open(MBOXLOGS, O_RDWR | O_NONBLOCK);
	mqd_t mboxCom = mq_open(MBOXCOMMUNICATION, O_RDWR | O_NONBLOCK);
	needToStop = TRUE;

	mq_send(mboxPalletStore, STOP_MESSAGE_QUEUE, sizeof (STOP_MESSAGE_QUEUE), MSG_LOW_PRIORITY);

	/* Waiting for simulation threads to end */
	UNLOCK(Valve);
	sleep(1);
	
	/* Unlocking other tasks
	   Warehouse... */
	sem_post(&SemWarehouse);
	/* Pallet... */
	sem_post(&SemSyncPrintPalette);
	UNLOCK(Palette);
	/* Printer... */
	sem_post(&SemPushBoxPrint);
	UNLOCK(Print);
	/* Parts packager... */
	sem_post(&SemSyncBoxPrint);
	sem_post(&SemNewPart);
	UNLOCK(Box);

	/* Closing Log thread */
	mq_send(mboxLogs, STOP_MESSAGE_QUEUE, sizeof (STOP_MESSAGE_QUEUE), MSG_LOW_PRIORITY);

	/* Note : No need to terminate doCommunication as it terminates by itself on shutdown order. */
	
	
}
