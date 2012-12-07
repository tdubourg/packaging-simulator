#include <stdio.h>
#include <stdlib.h>
#include "common.h"

sem_t SemSyncBoxImp;
sem_t SemPushBoxImp;
sem_t SemSyncImpPalette;
sem_t SemSocket;
sem_t SemStock;
sem_t SemNewPart;

pthread_mutex_t LockBox = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t LockImp = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t LockPalette = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t LockValve = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t CondValve = PTHREAD_COND_INITIALIZER;
pthread_cond_t CondBox = PTHREAD_COND_INITIALIZER;
pthread_cond_t CondPalette = PTHREAD_COND_INITIALIZER;
pthread_cond_t CondImp = PTHREAD_COND_INITIALIZER;
bool LockBoxValue;
bool LockImpValue;
bool LockPaletteValue;
bool LockValveValue;

int STOCKS = 0;
int PARTS_BY_BOX = 42;
int MAX_REFUSED_PARTS_BY_BOX = 42;

bool needToStop = TRUE;

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

int main(int argc, char** argv) {
	pthread_t tBox, tCommunication, tControl, tLog, tPalette, tPrint, tWarehouse;
	mqd_t mboxCommunication, mboxControl, mboxLogs, mboxPalletStore;
#ifdef SIMU_MODE
	pthread_t tSimuNewPart;
#endif

	pthread_mutex_lock(&LockBox);
	LockBoxValue = TRUE;
	pthread_cond_signal(&CondBox);
	pthread_mutex_unlock(&LockBox);

	pthread_mutex_lock(&LockImp);
	LockImpValue = TRUE;
	pthread_cond_signal(&CondImp);
	pthread_mutex_unlock(&LockImp);

	pthread_mutex_lock(&LockPalette);
	LockPaletteValue = TRUE;
	pthread_cond_signal(&CondPalette);
	pthread_mutex_unlock(&LockPalette);

    pthread_mutex_lock(&LockValve);
    LockValveValue = TRUE;
    pthread_cond_signal(&CondValve);
    pthread_mutex_unlock(&LockValve);

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
	// usleep(15 * 1000 * 1000);
	// DBG("main", "Main", "======= NOW LOCKING THE partsPackager task =======");
	// pthread_mutex_lock(&boxLock);
	// boxLockBool = FALSE;
	// pthread_cond_signal(&boxCond);
	// pthread_mutex_unlock(&boxLock);
	// usleep(7 * 1000 * 1000);
	// DBG("main", "Main", "======= NOW UUUUUNNNNNLOCKING THE partsPackager task =======");
	// pthread_mutex_lock(&boxLock);
	// boxLockBool = TRUE;
	// pthread_cond_signal(&boxCond);
	// pthread_mutex_unlock(&boxLock);
	
	// Wait for end of threads
	pthread_join(tCommunication, NULL);
	pthread_join(tBox, NULL);
	pthread_join(tPrint, NULL);
	pthread_join(tPalette, NULL);
	pthread_join(tWarehouse, NULL);
	pthread_join(tControl, NULL);
	pthread_join(tLog, NULL);

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

