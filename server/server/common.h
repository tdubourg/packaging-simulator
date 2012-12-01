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

#endif	/* COMMON_H */

