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

#define REFUSAL_RATE_FILE_NAME "refusalRate.txt"
#define SIMU_BOX_FILE_NAME "missingBox.txt"
#define SIMU_PRINT_FILE_NAME "printerError.txt"
#define SIMU_PALETTE_FILE_NAME "missingPalette.txt"

#define MBOXCOMMUNICATION "/MboxCommunication"
#define MBOXCONTROL "/MboxControl"
#define MBOXLOGS "/MboxLogs"
#define MBOXPALLETSTORE "/MboxPalletStore"

typedef unsigned char bool;
typedef enum batch_type_e {NO_BATCH, BATCH_TYPE_A, BATCH_TYPE_B} batch_type;

#define TRUE 1
#define FALSE 0
#define MAX_MSG_LEN 8192

#ifndef DBG
#define DBG
#endif
/* Uncomment to get a palette queue error */
/* #define TEST_PALETTE_QUEUE_ERROR */
#define SIMU_MODE

#ifdef DBG
#include "stdio.h"
#define DBGPRINT(A, B, C); printf((A));printf("::");printf((B));printf("(): ");printf((C));printf("\n");
#else
#define DBGPRINT(A, B, C);  
#endif

/* Kind of messages *********************************/
/* The message is an error, it will block something */
#define ERR 'E'
/* The message is a solve, it will unlock something */
#define SOLVE 'S'
#define SOLVE_MESSAGE "S"
/****************************************************/

/* Subjects *****************************************/
#define BOX 'B'
#define PALETTE 'P'
#define PRINT 'A'
#define WAREHOUSE 'W'
/* Inside the the doPalette task queue, where doPrint push something */
#define PALETTE_QUEUE 'Q'
/* Box rate */
#define BOX_REFUSED_RATE 'R'
/****************************************************/

/* @TODO: Write a bit of documentation to explain what those constants actually stand for */
#define ERR_LOG_PREFIX "ERROR "
#define ERR_BOX "EB"
/* No palette */
#define ERR_PALETTE "EP"
#define ERR_PRINT "EA"
#define ERR_WAREHOUSE "EW"
/* The following error is in the case the doPalette task queue is full and the doPrint one wants to push something to it */
#define ERR_PALETTE_QUEUE "EQ"
/* In case the refused rate of the currently packaging box is higher than the limit: */
#define ERR_BOX_REFUSED_RATE "ER"
#define PRODUCTION_IS_OVER_MSG "GAME OVER"

#define RESTART_AFTER_EMERGENCY_STOP "R"

#define MSG_HIGH_PRIORITY 3 /* for errors */
#define MSG_MEDIUM_PRIORITY 2 /* for normal message such as logs */
#define MSG_LOW_PRIORITY 1 /* for stop message */

#define STOP_MESSAGE_QUEUE "STOP_MESSAGE_QUEUE"
#define STOP_APP "QUIT"

#define EMERGENCY_STOP_OCCURED "EMERGENCY_STOP_OCCURED"
#define INIT_BATCH "INIT"

/* Set a value (S: bool) to a variable condtion (V) */
/* @TODO This is not clear at all, replace this macro by two macros : LOCK(V) and UNLOCK(V) */
#define SET(V, S) pthread_mutex_lock(&Lock ## V);\
       Lock ## V ## Value = S;\
       pthread_cond_signal(&Cond ## V);\
       pthread_mutex_unlock(&Lock ## V);

/* This macro basically checks that a "bool" Lock-type variable is FALSE
   and if it is not, it waits until the variable becomes TRUE (need notification for that, so, use the SET() macro!) */
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
#define LOG(M); if (mq_send(mboxLogger, M, MAX_MSG_LEN, MSG_MEDIUM_PRIORITY)) {\
					perror("Error while pushing a new log message");\
				}

#define LOG_ERR(M); if (mq_send(mboxLogger, M, MAX_MSG_LEN, MSG_HIGH_PRIORITY)) {\
					perror("Error while pushing an error log message");\
				}

#define ERR_MSG(M) if(mq_send(mboxControl, M, MAX_MSG_LEN, MSG_HIGH_PRIORITY)) {\
				perror("Error while sending the error to the Control Thread");\
			}

#define CONTROL_MSG(M) if(mq_send(mboxControl, M, MAX_MSG_LEN, MSG_MEDIUM_PRIORITY)) {\
				perror("Error while sending the message to the Control Thread");\
			}

/* Checks for end of the app and returns if end is reached. This macro is to be launched within the main function of a thread (return) */
#define CHECK_FOR_APP_END_AND_STOP(V); if (TRUE == needToStop)\
				{\
					DBGPRINT(V, "Main", "Ending current task");\
					return;\
				}
#define INIT_CHECK_FOR_APP_END(); extern bool needToStop;

#endif	/* COMMON_H */

