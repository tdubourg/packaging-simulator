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
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

#define LOG_FILE_NAME "log.txt" 

#define MBOXCOMMUNICATION "/MboxCommunication"
#define MBOXCONTROL "/MboxControl"
#define MBOXLOGS "/MboxLogs"
#define MBOXPALLETSTORE "/MboxPalletStore"

typedef unsigned char bool;


#define TRUE 1
#define FALSE 0
#define MAX_MSG_LEN 8192

#define DBG

#define SIMU_MODE

#ifdef DBG
#define DBG(A, B, C); printf((A));printf("::");printf((B));printf("(): ");printf((C));printf("\n");
#else
#define DBG(A, B, C);  
#endif

//@TODO: Write a bit of documentation to explain what those constants actually stand for
#define ERR_PALETTE "EP"
#define ERR_PRINT "EA"
#define ERR_WAREHOUSE "EW"
//* The following error is in the case the doPalette task queue is full and the doPrint one wants to push somthing to it
#define ERR_PALETTEQUEUE "EQ"
#define SOLVE_PALETTE "SP"
#define SOLVE_PRINT "SA"
#define SOLVE_WAREHOUSE "SW"
#define ERR_MSG_PRIORITY 2

#define STOP_MESSAGE_QUEUE "STOP_MESSAGE_QUEUE"

/* Set a value (S: bool) to a variable condtion (V) */
#define SET(V, S) pthread_mutex_lock(&Lock ## V);\
       Lock ## V ## Value = S;\
       pthread_cond_signal(&Cond ## V);\
       pthread_mutex_unlock(&Lock ## V);

/* Include a variable condition*/
#define INCLUDE(V) extern pthread_mutex_t Lock ## V;\
	extern pthread_cond_t Cond ## V;\
	extern bool Lock ## V ## Value;

#define INCLUDE_INTEGER(V) extern pthread_mutex_t Lock ## V;\
	extern pthread_cond_t Cond ## V;\
	extern int V ## Value;


#endif	/* COMMON_H */

