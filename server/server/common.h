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
extern mqd_t MboxCommunication;
extern mqd_t MboxControl;
extern mqd_t MboxLogs;
extern mqd_t MboxPalletStore;

extern int STOCKS;
extern int PARTS_BY_BOX;
extern int MAX_REFUSED_PARTS_BY_BOX;

typedef unsigned char bool;
#define TRUE 1
#define FALSE 0

#endif	/* COMMON_H */

