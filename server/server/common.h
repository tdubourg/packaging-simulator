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

/* Location of log file */
#define LOG_FILE_NAME "log.txt" 

/***** Location of messages queues ********************************************/
#define MBOXCOMMUNICATION "/MboxCommunication"
#define MBOXCONTROL "/MboxControl"
#define MBOXLOGS "/MboxLogs"
#define MBOXPALLETSTORE "/MboxPalletStore"
/******************************************************************************/

/***** Boolean facilities *****************************************************/
typedef unsigned char bool;
typedef enum batch_type_e {NO_BATCH, BATCH_TYPE_A, BATCH_TYPE_B} batch_type;

#define TRUE 1
#define FALSE 0
/******************************************************************************/

#ifndef DBG
#define DBG
#endif
/* Uncomment to get a palette queue error */
/* #define TEST_PALETTE_QUEUE_ERROR */
#define SIMU_MODE

/***** Debug helpers **********************************************************/

/*** File used to generate an error **********************/
#define REFUSAL_RATE_FILE_NAME "refusalRate.txt"
#define SIMU_BOX_FILE_NAME "missingBox.txt"
#define SIMU_PRINT_FILE_NAME "printerError.txt"
#define SIMU_PALETTE_FILE_NAME "missingPalette.txt"
/*********************************************************/

#ifdef DBG
#include "stdio.h"
#define DBGPRINT(A, B, C); printf((A));printf("::");printf((B));printf("(): ");printf((C));printf("\n");
#else
#define DBGPRINT(A, B, C);  
#endif
/******************************************************************************/

/***** Messages ***************************************************************/
/* Lenght of messages in message queues */
#define MAX_MSG_LEN 8192
/*** Kind of messages ************************************/
/* The message is an error, it will block something */
#define ERR 'E'
/* The message is a solve, it will unlock something */
#define SOLVE 'S'
#define SOLVE_MESSAGE "S"
/*********************************************************/

/*** Subjects ********************************************/
#define BOX 'B'
#define PALETTE 'P'
#define PRINT 'A'
#define WAREHOUSE 'W'
/* Inside the the doPalette task queue, where doPrint push something */
#define PALETTE_QUEUE 'Q'
/* Box rate */
#define BOX_REFUSED_RATE 'R'
/*********************************************************/
/* Error prefix for all error message sent to the client*/
#define ERR_LOG_PREFIX "ERROR " 
/* Error notifying that there is no box to stock the new piece*/
#define ERR_BOX "EB" 
/* Error notifying that there is no pallet to stock the new box*/
#define ERR_PALETTE "EP" 
/* Error message notifying that the printer is empty*/
#define ERR_PRINT "EA" 
/* Error that shouldn't happen : the Warehouse is full */
#define ERR_WAREHOUSE "EW" 
/* The following error is in the case the doPalette task queue is full and the
 * doPrint one wants to push something to it */
#define ERR_PALETTE_QUEUE "EQ"
/* In case the refused rate of the currently packaging box is higher than the limit */
#define ERR_BOX_REFUSED_RATE "ER" 

/* Message sent to the client to notify the end of a batch, this is a special LOG MESSAGE that will be parsed by the client */
#define PRODUCTION_IS_OVER_MSG "GAME OVER"

/* Special logs that will be parse by the network client to detecte emergency stop */
#define EMERGENCY_STOP_MSG "EMERGENCY_STOP_OCCURED"

/* Message sent from the client to restart the production after an emergency stop*/
#define RESTART_AFTER_EMERGENCY_STOP "R" 

/* Message queue priority for errors */
#define MSG_HIGH_PRIORITY 3 
/* Message queue priority for normal message such as logs */
#define MSG_MEDIUM_PRIORITY 2 
 /* Message queue priority for stop message */
#define MSG_LOW_PRIORITY 1

/* message to send to every message queue to terminate application */
#define STOP_MESSAGE_QUEUE "STOP_MESSAGE_QUEUE" 
/* Message sent from the client to terminate application */
#define STOP_APP "QUIT" 
/* Message sent from the client to initiate a new batch */
#define INIT_BATCH "INIT" 

/******************************************************************************/

/***** Variables condition ****************************************************/
/* Set a value (S: bool) to a variable condtion (V) */
#define SET(V, S); pthread_mutex_lock(&Lock ## V);\
       Lock ## V ## Value = S;\
       pthread_cond_signal(&Cond ## V);\
       pthread_mutex_unlock(&Lock ## V);

/* Lock a variable condtion (V) */
#define LOCK(V) SET(V, TRUE)
/* Unlock a variable condtion (V) */
#define UNLOCK(V) SET(V, FALSE)

/* This macro basically checks that a "bool" Lock-type variable is FALSE
 * and if it is not, it waits until the variable becomes TRUE (need notification
   for that, so, use the LOCK() macro!) */
#define CHECK_WAIT_BOOL(V) pthread_mutex_lock(&Lock ## V);\
		while(Lock ## V ## Value) {\
			pthread_cond_wait(&Cond ## V, &Lock ## V);\
		}\
		pthread_mutex_unlock(&Lock ## V);

/* Include a variable condition */
#define INCLUDE(V) extern pthread_mutex_t Lock ## V;\
	extern pthread_cond_t Cond ## V;\
	extern bool Lock ## V ## Value;

/* Include a variable condition which is an integer */
#define INCLUDE_INTEGER(V) extern pthread_mutex_t Lock ## V;\
	extern pthread_cond_t Cond ## V;\
	extern int V ## Value;
/******************************************************************************/

#define INIT_LOGGER(); mqd_t mboxLogger = mq_open(MBOXLOGS, O_RDWR | O_NONBLOCK);
#define INIT_CONTROL(); mqd_t mboxControl = mq_open(MBOXCONTROL, O_RDWR | O_NONBLOCK);
#define LOG(M); if (mq_send(mboxLogger, M, sizeof(M), MSG_MEDIUM_PRIORITY)) {\
					perror("Error while pushing a new log message");\
				}

#define LOG_ERR(M); if (mq_send(mboxLogger, M, sizeof(M), MSG_HIGH_PRIORITY)) {\
					perror("Error while pushing an error log message");\
				}

#define ERR_MSG(M) if(mq_send(mboxControl, M, sizeof(M), MSG_HIGH_PRIORITY)) {\
				perror("Error while sending the error to the Control Thread");\
			}

#define CONTROL_MSG(M) if(mq_send(mboxControl, M, sizeof(M), MSG_MEDIUM_PRIORITY)) {\
				perror("Error while sending the message to the Control Thread");\
			}

/* Checks for end of the app and returns if end is reached.
 * This macro is to be launched within the main function of a thread (return) */
#define CHECK_FOR_APP_END_AND_STOP(V); if (TRUE == NeedToStop)\
				{\
					DBGPRINT(V, "Main", "Ending current task");\
					return;\
				}
#define INIT_CHECK_FOR_APP_END(); extern bool NeedToStop;

#endif	/* COMMON_H */

