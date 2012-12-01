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

/*
 * 
 */
int main(int argc, char** argv)
{
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
    
    // Wait
    
    mq_close(MboxCommunication);
    mq_close(MboxControl);
    mq_close(MboxLogs);
    mq_close(MboxPalletStore);
    return (EXIT_SUCCESS);
}

