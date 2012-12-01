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
extern sem_t SemSyncBoxIm;
extern sem_t SemSyncImpPalette;
extern sem_t SemSocket;
extern sem_t SemStock;

#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
mqd_t MboxCommunication;
mqd_t MboxControl;
mqd_t MboxLogs;
mqd_t MboxPalletStore;

#endif	/* COMMON_H */

