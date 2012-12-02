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
sem_t SemSyncBoxIm;
sem_t SemSyncImpPalette;
sem_t SemSocket;
sem_t SemStock;

mqd_t MboxCommunication;
mqd_t MboxControl;
mqd_t MboxLogs;
mqd_t MboxPalletStore;

int STOCKS;
int PARTS_BY_BOX;
int MAX_REFUSED_PARTS_BY_BOX;

#include "doBox.h"
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
    
    STOCKS = 0;
    PARTS_BY_BOX = 0;
    MAX_REFUSED_PARTS_BY_BOX = 0;
    
    sem_init(&SemCtrlBox, 0, 1);
    sem_init(&SemCtrlPallet, 0, 1);
    sem_init(&SemCtrlImp, 0, 1);
    sem_init(&SemSyncBoxIm, 0, 1);
    sem_init(&SemSyncImpPalette, 0, 1);
    sem_init(&SemSocket, 0, 1);
    sem_init(&SemStock, 0, 1);
    
    MboxCommunication = mq_open("MboxCommunication", O_RDWR);
    MboxControl = mq_open("MboxControl", O_RDWR);
    MboxLogs = mq_open("MboxLogs", O_RDWR);
    MboxPalletStore = mq_open("MboxPalletStore", O_RDWR);
    
    pthread_create(&tLog, NULL, doLog, NULL);
    pthread_create(&tControl, NULL, doControl, NULL);
    pthread_create(&tWarehouse, NULL, doWarehouse, NULL);
    pthread_create(&tPalette, NULL, doPalette, NULL);
    pthread_create(&tPrint, NULL, doPrint, NULL);
    pthread_create(&tBox, NULL, doBox, NULL);
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
    return (EXIT_SUCCESS);
}

