/* 
 * File:   common.h
 * Author: black
 *
 * Created on December 1, 2012, 1:14 PM
 */

#ifndef COMMON_H
#define	COMMON_H

#include <pthread.h>
#include <semaphore.h>

extern sem_t SemCtrlBox;
extern sem_t SemCtrlPallet;
extern sem_t SemCtrlImp;
extern sem_t SemSyncBoxImp;
extern sem_t SemSyncImpPalette;
extern sem_t SemSocket;
extern sem_t SemStock;

#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
//extern mqd_t MboxCommunication;
//extern mqd_t MboxControl;
//extern mqd_t MboxLogs;
//extern mqd_t MboxPalletStore;
#define MBOX_COM_NAME "/MboxCommunication"
#define MBOX_CTRL_NAME "/MboxControl"
#define MBOX_LOG_NAME "/MboxLogs"
#define MBOX_PALLET_STORE_NAME "/MboxPalletStore"

extern int STOCKS;
extern int PARTS_BY_BOX;
extern int MAX_REFUSED_PARTS_BY_BOX;

typedef unsigned char bool;
#define TRUE 1
#define FALSE 0
#define MAX_MSG_LEN 8192

#endif	/* COMMON_H */

