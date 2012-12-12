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
//* In case the refused rate of the currently packaging box is higher than the limit:
#define ERR_BOX_REFUSED_RATE "ER"

#define SOLVE_PALETTE "SP"
#define SOLVE_PRINT "SA"
#define SOLVE_WAREHOUSE "SW"
#define ERR_MSG_PRIORITY 2
#define LOG_MSG_PRIORITY 1 //@TODO Check that 1 is lower than 2, in terms of mq messages priorities

#define STOP_MESSAGE_QUEUE "STOP_MESSAGE_QUEUE"
#define STOP_APP "QUIT"

/* Set a value (S: bool) to a variable condtion (V) */
#define SET(V, S) pthread_mutex_lock(&Lock ## V);\
       Lock ## V ## Value = S;\
       pthread_cond_signal(&Cond ## V);\
       pthread_mutex_unlock(&Lock ## V);

//* This macro basically checks that a "bool" Lock-type variable is FALSE
//* and if it is not, it waits until the variable becomes TRUE (need notification for that, so, use the SET() macro!)
#define CHECK_WAIT_BOOL(V) pthread_mutex_lock(&Lock ## V);\
		while(Lock ## V ## Value) {\
			pthread_cond_wait(&Cond ## V, &Lock ## V);\
		}\
		pthread_mutex_unlock(&Lock ## V);

/* Include a variable condition*/
#define INCLUDE(V) extern pthread_mutex_t Lock ## V;\
	extern pthread_cond_t Cond ## V;\
	extern bool Lock ## V ## Value;

#define INCLUDE_INTEGER(V) extern pthread_mutex_t Lock ## V;\
	extern pthread_cond_t Cond ## V;\
	extern int V ## Value;

#define INIT_LOGGER(); mqd_t mboxLogger = mq_open(MBOXLOGS, O_RDWR | O_NONBLOCK);
#define INIT_CONTROL(); mqd_t mboxControl = mq_open(MBOXCONTROL, O_RDWR | O_NONBLOCK);
#define LOG(M); if (mq_send(mboxLogger, M, MAX_MSG_LEN, LOG_MSG_PRIORITY)) {\
					perror("Error while pushing a new log message");\
				}

#define ERR_MSG(M) if(mq_send(mboxControl, M, MAX_MSG_LEN, ERR_MSG_PRIORITY)) {\
				perror("Error while sending the error to the Control Thread");\
			}

#endif	/* COMMON_H */

