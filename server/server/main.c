#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "common.h"

sem_t SemSyncBoxImp;
sem_t SemPushBoxImp;
sem_t SemSyncImpPalette;
sem_t SemSocket;
sem_t SemStock;
sem_t SemNewPart;
sem_t SemWarehouse;

pthread_mutex_t LockBox = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t LockImp = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t LockPalette = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t LockValve = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t LockPrintPaletteQueue = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t LockWarehouseStorageData = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t CondValve = PTHREAD_COND_INITIALIZER;
pthread_cond_t CondBox = PTHREAD_COND_INITIALIZER;
pthread_cond_t CondPalette = PTHREAD_COND_INITIALIZER;
pthread_cond_t CondImp = PTHREAD_COND_INITIALIZER;
pthread_cond_t CondPrintPaletteQueue = PTHREAD_COND_INITIALIZER;

bool LockBoxValue;
bool LockImpValue;
bool LockPaletteValue;
bool LockValveValue;
int PrintPaletteQueueValue = 0;
int AStock = 0, BStock = 0; //* globals for storing the current stock of A/B palettes (integer = number of palette of A or B that we currently have in stock)
batch_type CurrentBatchType;
int CurrentBatchProdMax = 100;//* number of palettes we have to produce for the current batch
int CurrentProducedBoxes = 0;

int STOCKS = 0;
int PARTS_BY_BOX = 5;
int BOXES_BY_PALETTE = 5;
int MAX_REFUSED_PARTS_BY_BOX = 42;
int MAX_BOXES_QUEUE = 10;


bool needToStop = FALSE;//@TODO rename this variable (global should start with a capital letter, and a better name might be useful as well)
static mqd_t mboxControl;

#include "partsPackager.h"
#include "doCommunication.h"
#include "doControl.h"
#include "doLog.h"
#include "doPalette.h"
#include "doPrint.h"
#include "doWarehouse.h"
#include "simu/newpart.c"

#ifdef DBG
#include "time.h"
#endif

static void handler_alert(int);

int main(int argc, char** argv) {
	pthread_t tBox, tCommunication, tControl, tLog, tPalette, tPrint, tWarehouse;
	mqd_t mboxCommunication, mboxLogs, mboxPalletStore;
	#ifdef SIMU_MODE
	pthread_t tSimuNewPart;
	#endif
	signal(SIGINT, handler_alert);
	
	//* No need to block everything, anyway everything will be hanging on until there is parts coming in
	SET(Box, FALSE);
	SET(Palette, FALSE);
	SET(Imp, FALSE);
	//* Te valve, though, has to be closed, at the start of the app
	SET(Valve, TRUE);

	sem_init(&SemSyncBoxImp, 0, 1);
	sem_init(&SemPushBoxImp, 0, 0);
	sem_init(&SemSyncImpPalette, 0, 1);
	sem_init(&SemSocket, 0, 1);
	sem_init(&SemStock, 0, 1);


	sem_init(&SemNewPart, 0, 0);

	// Open message queues
	mboxCommunication = mq_open(MBOXCOMMUNICATION, O_RDWR | O_CREAT, S_IRWXU | S_IRWXG, NULL);
	mboxControl = mq_open(MBOXCONTROL, O_RDWR | O_CREAT, S_IRWXU | S_IRWXG, NULL);
	mboxLogs = mq_open(MBOXLOGS, O_RDWR | O_CREAT, S_IRWXU | S_IRWXG, NULL);
	mboxPalletStore = mq_open(MBOXPALLETSTORE, O_RDWR | O_CREAT, S_IRWXU | S_IRWXG, NULL);

	//wait
	
	pthread_create(&tLog, NULL, doLog, NULL);
	pthread_create(&tControl, NULL, doControl, NULL);
	pthread_create(&tWarehouse, NULL, doWarehouse, NULL);
	pthread_create(&tPalette, NULL, doPalette, NULL);
	pthread_create(&tPrint, NULL, doPrint, NULL);
	pthread_create(&tBox, NULL, partsPackager, NULL);
	pthread_create(&tCommunication, NULL, doCommunication, NULL);
#ifdef SIMU_MODE
	pthread_create(&tSimuNewPart, NULL, newpart, NULL);
#endif


	// Wait
	//@TODO : Remove those lines that are used for testing purposes
	// usleep(7 * 1000 * 1000);
	// DBG("main", "Main", "======= NOW UNLOCKING THE partsPackager task =======");
	// SET(Box, FALSE);

	// usleep(5 * 1000 * 1000);
	// CurrentBatchType = BATCH_TYPE_A;
	// DBG("main", "Main", "======= NOW All the rest! THE newpart task =======");
	// SET(Valve, FALSE)
	// SET(Palette, FALSE);
	// SET(Imp, FALSE);
	// SET(Valve, FALSE);

	mq_send(mboxLogs,"Je PUSH depuis une boite aux lettres",36,1);
	
	// Wait for end of threads
	pthread_join(tCommunication, NULL);
	pthread_join(tBox, NULL);
	pthread_join(tPrint, NULL);
	pthread_join(tPalette, NULL);
	pthread_join(tWarehouse, NULL);
	pthread_join(tControl, NULL);
	pthread_join(tLog, NULL);
#ifdef SIMU_MODE
	pthread_join(tSimuNewPart, NULL);
#endif

	// Deleting message queue
	mq_close(mboxCommunication);
	mq_close(mboxControl);
	mq_close(mboxLogs);
	mq_close(mboxPalletStore);

	// Deleting sems
	sem_destroy(&SemStock);
	sem_destroy(&SemSocket);
	sem_destroy(&SemSyncImpPalette);
	sem_destroy(&SemSyncBoxImp);


	return (EXIT_SUCCESS);
}


static void handler_alert(int n)
{
	#ifdef DBG
	static bool s = FALSE;
	s = !s;
	if (!s)
	{
		mq_send(mboxControl, "R", 2, 5);
		return;
	}
	printf("Alert\n");
	#endif
	SET(Box, FALSE);
	SET(Palette, FALSE);
	SET(Imp, FALSE);
	SET(Valve, FALSE);
}