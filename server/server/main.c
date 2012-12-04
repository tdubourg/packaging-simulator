#include <stdio.h>
#include <stdlib.h>
#include "common.h"

sem_t SemCtrlBox;
sem_t SemCtrlPallet;
sem_t SemCtrlImp;
sem_t SemSyncBoxImp;
sem_t SemSyncImpPalette;
sem_t SemSocket;
sem_t SemStock;

int STOCKS = 0;
int PARTS_BY_BOX = 42;
int MAX_REFUSED_PARTS_BY_BOX = 42;

#include "partsPackager.h"
#include "doCommunication.h"
#include "doControl.h"
#include "doLog.h"
#include "doPalette.h"
#include "doPrint.h"
#include "doWarehouse.h"
#include "simu/newpart.c"

int main(int argc, char** argv)
{
    pthread_t tBox, tCommunication, tControl, tLog, tPalette, tPrint, tWarehouse;
	mqd_t mboxCommunication, mboxControl, mboxLogs, mboxPalletStore;
    
    sem_init(&SemCtrlBox, 0, 1);
    sem_init(&SemCtrlPallet, 0, 1);
    sem_init(&SemCtrlImp, 0, 1);
    sem_init(&SemSyncBoxImp, 0, 1);
    sem_init(&SemSyncImpPalette, 0, 1);
    sem_init(&SemSocket, 0, 1);
    sem_init(&SemStock, 0, 1);

#ifdef SIMU_MODE
extern sem_t SemNewPart;
sem_init(&SemNewPart, 0, 1);
#endif
	// Open message queues
    mboxCommunication = mq_open(MBOXCOMMUNICATION, O_RDWR | O_CREAT, S_IRWXU | S_IRWXG, NULL);
    mboxControl = mq_open(MBOXCONTROL, O_RDWR | O_CREAT, S_IRWXU | S_IRWXG, NULL);
    mboxLogs = mq_open(MBOXLOGS, O_RDWR | O_CREAT, S_IRWXU | S_IRWXG, NULL);
    mboxPalletStore = mq_open(MBOXPALLETSTORE, O_RDWR | O_CREAT, S_IRWXU | S_IRWXG, NULL);
    
    pthread_create(&tLog, NULL, doLog, NULL);
    pthread_create(&tControl, NULL, doControl, NULL);
    pthread_create(&tWarehouse, NULL, doWarehouse, NULL);
    pthread_create(&tPalette, NULL, doPalette, NULL);
    pthread_create(&tPrint, NULL, doPrint, NULL);
    pthread_create(&tBox, NULL, partsPackager, NULL);
    pthread_create(&tCommunication, NULL, doCommunication, NULL);
    
    // Wait
    
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
    sem_destroy(&SemCtrlImp);
    sem_destroy(&SemCtrlPallet);
    sem_destroy(&SemCtrlBox);
    

    return (EXIT_SUCCESS);
}

