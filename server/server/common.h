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

#define LOG_FILE_NAME "log.txt" 

#define MBOXCOMMUNICATION "/MboxCommunication"
#define MBOXCONTROL "/MboxControl"
#define MBOXLOGS "/MboxLogs"
#define MBOXPALLETSTORE "/MboxPalletStore"

extern int STOCKS;
extern int PARTS_BY_BOX;
extern int MAX_REFUSED_PARTS_BY_BOX;

typedef unsigned char bool;
#define TRUE 1
#define FALSE 0
#define MAX_MSG_LEN 8192

#define DBG
#define SIMU_MODE

#define ERR_PALETTE "EP"
#define ERR_PRINT "EA"
#define ERR_WAREHOUSE "EW"
#define SOLVE_PALETTE "SP"
#define SOLVE_PRINT "SA"
#define SOLVE_WAREHOUSE "SW"

// Debug stuff : console-logging macro ! better with a macro : will be deleted upon compilation
#ifdef DBG
#define DBG(A, B, C); printf((A));printf("::");printf((B));printf("(): ");printf((C));printf("\n");
#else
#define DBG(A, B, C);  
#endif



#endif	/* COMMON_H */

