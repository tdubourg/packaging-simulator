/* 
 * File:   main.c
 * Author: black
 *
 * Created on November 30, 2012, 11:32 AM
 */

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

mqd_t MboxCommunication;
mqd_t MboxControl;
mqd_t MboxLogs;
mqd_t MboxPalletStore;

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

/*
 * 
 */
int main(int argc, char** argv)
{
    pthread_t tBox, tCommunication, tControl, tLog, tPalette, tPrint, tWarehouse;
    
    sem_init(&SemCtrlBox, 0, 1);
    sem_init(&SemCtrlPallet, 0, 1);
    sem_init(&SemCtrlImp, 0, 1);
    sem_init(&SemSyncBoxImp, 0, 1);
    sem_init(&SemSyncImpPalette, 0, 1);
    sem_init(&SemSocket, 0, 1);
    sem_init(&SemStock, 0, 1);
    
    MboxCommunication = mq_open(MBOX_COM_NAME, O_RDWR);
    MboxControl = mq_open(MBOX_CTRL_NAME, O_RDWR);
    MboxLogs = mq_open(MBOX_LOG_NAME, O_RDWR | O_CREAT, S_IRWXU | S_IRWXG, NULL);
    MboxPalletStore = mq_open(MBOX_PALLET_STORE_NAME, O_RDWR);
    //mq_open(MAIN_QNAME, O_RDWR | O_CREAT, S_IRWXU | S_IRWXG, NULL);
    
    pthread_create(&tLog, NULL, doLog, NULL);
    pthread_create(&tControl, NULL, doControl, NULL);
    pthread_create(&tWarehouse, NULL, doWarehouse, NULL);
    pthread_create(&tPalette, NULL, doPalette, NULL);
    pthread_create(&tPrint, NULL, doPrint, NULL);
    pthread_create(&tBox, NULL, partsPackager, NULL);
    pthread_create(&tCommunication, NULL, doCommunication, NULL);
    
    // Wait
    
    pthread_join(tCommunication, NULL);
    pthread_join(tBox, NULL);
    pthread_join(tPrint, NULL);
    pthread_join(tPalette, NULL);
    pthread_join(tWarehouse, NULL);
    pthread_join(tControl, NULL);
    pthread_join(tLog, NULL);
    
    mq_close(MboxCommunication);
    mq_close(MboxControl);
    mq_close(MboxLogs);
    mq_close(MboxPalletStore);

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

