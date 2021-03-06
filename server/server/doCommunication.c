#include "doCommunication.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define PUSH_PORT 30035
#define PULL_PORT 13003

#define STATE_MSG_PREFIX "STATE"
#define SHUTDOWN_CMD "SHUTDOWN\r\n"
#define DISCONNECT_CMD "DISCONNECT\r\n"
#define ACK_MSG "ACK\r\n"
#define RESTART_CMD "RESTART\r\n"
#define CMD_MSG_PREFIXE "CMD"

/*
 * Send the error on the standard output
 */
static void error(const char *msg);

/*
 * Log sent to the client thread
 */
static void *doPush(void *p);

/*
 * Command from the client thread
 */
void *doCommunication(void *p) {
	/* INIT *******************************************************************/
	extern int AStock, BStock;
	extern pthread_mutex_t LockWarehouseStorageData;
	pthread_t tPush;
	INIT_CONTROL();

	/* Starting the pushing thread */
	pthread_create(&tPush, NULL, doPush, NULL);

	/* Set the letterBox with push thread */
	mqd_t mboxCom = mq_open(MBOXCOMMUNICATION, O_RDWR);

	/* Set sockets and buffer */
	int sockfd, newsockfd, portno;
	socklen_t clilen;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	int n;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	int optval = 1;
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof (int));

	if (sockfd < 0)
		error("ERROR opening socket");

	bzero((char *) &serv_addr, sizeof (serv_addr));
	portno = PULL_PORT;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof (serv_addr)) < 0)
		error("ERROR on binding");

	/* MAIN LOOP **************************************************************/
	/* Waiting connection loop */
	for (;;) {
		listen(sockfd, 5);
		clilen = sizeof (cli_addr);
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

		if (newsockfd < 0)
			error("ERROR on accept");

		/* Client communication loop */
		for (;;) {
			bzero(buffer, 256);
			n = read(newsockfd, buffer, 255);
			if (n < 0) error("ERROR reading from socket");

			/*When client want to disconnect from the server*/
			if (strcmp(buffer, DISCONNECT_CMD) == 0) {
				mq_send(mboxCom, DISCONNECT_CMD, sizeof (DISCONNECT_CMD), MSG_HIGH_PRIORITY);
				close(newsockfd);
				break;

				/*When client want to shutdown the server*/
			} else if (strcmp(buffer, SHUTDOWN_CMD) == 0) {
				ERR_MSG(STOP_APP)
				close(newsockfd);
				close(sockfd);
				return;

				/*When client restart production after a failure*/
			} else if (strcmp(buffer, RESTART_CMD) == 0) {
				ERR_MSG(SOLVE_MESSAGE)
			} else {
				/*Pointer used in strtok_r function*/
				char * saveptr1;

				/* Buffer used for strtok_r function, which is the actual copy
				 * of the socket buffer. */
				char tokenBuffer[256];
				strcpy(tokenBuffer, buffer);

				char * token = strtok_r(tokenBuffer, "-", &saveptr1);

				/* If the message sent by the client is a stock command */
				if (!strcmp(token, CMD_MSG_PREFIXE)) {
					token = strtok_r(NULL, "-", &saveptr1);
					int cmdA = atoi(token);
					token = strtok_r(NULL, "-", &saveptr1);
					int cmdB = atoi(token);

					pthread_mutex_lock(&LockWarehouseStorageData);
					AStock = AStock - cmdA;
					BStock = BStock - cmdB;
					pthread_mutex_unlock(&LockWarehouseStorageData);

					/* If it's not one of the cases above, the message is sent
					 * to the controller */
				} else {
					ERR_MSG(buffer)
				}
			}

			n = write(newsockfd, ACK_MSG, sizeof (ACK_MSG));
			if (n < 0)
				error("ERROR writing to socket");
		}
	}
	return 0;
}

/*
 * Send the error on the standard output
 */
static void error(const char *msg) {
	perror(msg);
}

/*
 * Log sent to the client thread
 */
static void *doPush(void *p) {
	/* INIT *******************************************************************/
	extern int AStock, BStock, CurrentProducedBoxes, CurrentBatchRefusedPartsNumber;
	extern pthread_mutex_t LockWarehouseStorageData;

	int sentAStock, sentBStock;
	char stockBuffer[MAX_MSG_LEN + 1];

	/* Set the log buffer */
	char logsBuffer[MAX_MSG_LEN + 1];
	/* Init message queue */
	mqd_t mboxCom = mq_open(MBOXCOMMUNICATION, O_RDWR);

	/* Set the sockets */
	int sockfd, newsockfd, portno;
	socklen_t clilen;
	struct sockaddr_in serv_addr, cli_addr;
	int n;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	int optval = 1;
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof (int));

	if (sockfd < 0)
		error("ERROR opening socket");
	bzero((char *) &serv_addr, sizeof (serv_addr));
	portno = PUSH_PORT;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof (serv_addr)) < 0)
		error("ERROR on binding");

	/* MAIN LOOP **************************************************************/
	/* Waiting connection loop */
	for (;;) {
		listen(sockfd, 5);
		clilen = sizeof (cli_addr);
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

		if (newsockfd < 0)
			error("ERROR on accept");

		/* Pushing loop whenever there is a log in the message queue */
		for (;;) {

			int bytes_read = mq_receive(mboxCom, logsBuffer, MAX_MSG_LEN, NULL);

			/* Check if the thread has to shutdown */
			if (strcmp(logsBuffer, STOP_MESSAGE_QUEUE) == 0) {
				close(newsockfd);
				close(sockfd);
				return 0;
			}

			/* Check if there is a disconnection request from the client */
			if (strcmp(logsBuffer, DISCONNECT_CMD) == 0) {
				close(newsockfd);
				break;
			}

			if (bytes_read == -1) {
				perror("[CommunicationThread] Failed to receive from LogThread");

				/* Send the logs */
			} else {
				strcat(logsBuffer, "\r\n");
				n = write(newsockfd, logsBuffer, strlen(logsBuffer));
				if (n < 0)
					error("ERROR writing to socket");

				/* Got the stock state */
				pthread_mutex_lock(&LockWarehouseStorageData);
				sentAStock = AStock;
				sentBStock = BStock;
				pthread_mutex_unlock(&LockWarehouseStorageData);

				/* Send the stock state */
				bzero(stockBuffer, sizeof (stockBuffer));
				sprintf(stockBuffer, "%s-%d-%d-%d-%d\r\n", STATE_MSG_PREFIX,
						sentAStock, sentBStock, CurrentProducedBoxes,
						CurrentBatchRefusedPartsNumber);

				n = write(newsockfd, stockBuffer, strlen(stockBuffer));
				if (n < 0)
					error("ERROR writing to socket");
			}
		}
	}
	return 0;
}