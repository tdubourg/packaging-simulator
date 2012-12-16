#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <mqueue.h>
#include "common.h"

sem_t SemSyncBoxPrint;
sem_t SemPushBoxPrint;
sem_t SemSyncPrintPalette;
sem_t SemSocket;
sem_t SemNewPart;
sem_t SemWarehouse;

pthread_mutex_t LockBox = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t LockPrint = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t LockPalette = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t LockValve = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t LockPrintPaletteQueue = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t LockWarehouseStorageData = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t CondValve = PTHREAD_COND_INITIALIZER;
pthread_cond_t CondBox = PTHREAD_COND_INITIALIZER;
pthread_cond_t CondPalette = PTHREAD_COND_INITIALIZER;
pthread_cond_t CondPrint = PTHREAD_COND_INITIALIZER;
pthread_cond_t CondPrintPaletteQueue = PTHREAD_COND_INITIALIZER;

bool LockBoxValue;
bool LockPrintValue;
bool LockPaletteValue;
bool LockValveValue;
int PrintPaletteQueueValue = 0;
int AStock = 0, BStock = 0; /* globals for storing the current stock of A/B palettes (integer = number of palettes of A or B that we currently have in stock) */

batch_type CurrentBatchType;
int CurrentBatchProdMax = 100;/* number of palettes we have to produce for the current batch */
int CurrentProducedBoxes = 0;
int CurrentBatchRefusedPartsNumber = 0;

int STOCKS = 0;
int PARTS_BY_BOX = 5;
int BOXES_BY_PALETTE = 5;
int MAX_REFUSED_PARTS_BY_BOX = 42;
int MAX_BOXES_QUEUE = 10;


bool needToStop = FALSE;/* @TODO rename this variable (global should start with a capital letter, and a better name might be useful as well) */
static mqd_t mboxControl;

#include "doBox.h"
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
	
	/* We block everything at the beginning in order to receive potential errors later and be able to send them to the client */
	LOCK(Box);
	LOCK(Palette);
	LOCK(Print);
	/* The valve, though, has to be closed, at the start of the app */
	SET(Valve, TRUE);
	LOCK(Valve);

	sem_init(&SemSyncBoxPrint, 0, 1);
	sem_init(&SemPushBoxPrint, 0, 0);
	sem_init(&SemSyncPrintPalette, 0, 1);
	sem_init(&SemSocket, 0, 1);


	sem_init(&SemNewPart, 0, 0);

	/* Open message queues */
	/* struct mq_attr attr;
	   attr.mq_maxmsg = 1000; */
	mboxCommunication = mq_open(MBOXCOMMUNICATION, O_RDWR | O_CREAT, S_IRWXU | S_IRWXG, NULL);
	mboxControl = mq_open(MBOXCONTROL, O_RDWR | O_CREAT, S_IRWXU | S_IRWXG, NULL);
	mboxLogs = mq_open(MBOXLOGS, O_RDWR | O_CREAT, S_IRWXU | S_IRWXG, NULL);
	mboxPalletStore = mq_open(MBOXPALLETSTORE, O_RDWR | O_CREAT, S_IRWXU | S_IRWXG, NULL);

	/* Wait */
	
	pthread_create(&tLog, NULL, doLog, NULL);
	pthread_create(&tControl, NULL, doControl, NULL);
	pthread_create(&tWarehouse, NULL, doWarehouse, NULL);
	pthread_create(&tPalette, NULL, doPalette, NULL);
	pthread_create(&tPrint, NULL, doPrint, NULL);
	pthread_create(&tBox, NULL, doBox, NULL);
	pthread_create(&tCommunication, NULL, doCommunication, NULL);
#ifdef SIMU_MODE
	pthread_create(&tSimuNewPart, NULL, newpart, NULL);
#endif
	
	/* char* msg = "INIT-A-3-40-8-1";
	   mq_send(mboxControl,msg,strlen(msg),MSG_HIGH_PRIORITY); */
	
	/* Wait for end of threads */
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

	/* Deleting message queue */
	mq_close(mboxCommunication);
	mq_close(mboxControl);
	mq_close(mboxLogs);
	mq_close(mboxPalletStore);

	/* Deleting sems */
	sem_destroy(&SemSocket);
	sem_destroy(&SemSyncPrintPalette);
	sem_destroy(&SemSyncBoxPrint);


	return (EXIT_SUCCESS);
}

static void handler_alert(int n)
{
	LOCK(Box);
	LOCK(Palette);
	LOCK(Print);
	LOCK(Valve);
	INIT_LOGGER();
	LOG(EMERGENCY_STOP_MSG);
}
