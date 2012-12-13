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

void error(const char *msg) {
	perror(msg);
	exit(1);
}

void *doPush(void *p) {

	/*Mise en place du buffer de logs*/
	char logsBuffer[MAX_MSG_LEN + 1];
	/*Mise en place de la boite aux lettres*/
	mqd_t mboxCom = mq_open(MBOXCOMMUNICATION, O_RDWR);

	/*Création des sockets*/
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
	portno = PUSH_PORT;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof (serv_addr)) < 0)
		error("ERROR on binding");

	/*Boucle d'attente de connexion*/
	for (;;) {
		listen(sockfd, 5);
		clilen = sizeof (cli_addr);
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

		if (newsockfd < 0)
			error("ERROR on accept");

		/*Boucle d'envoie en push lors de reception de logs
		 *dans la boite aux lettres*/
		for (;;) {
			
			int bytes_read = mq_receive(mboxCom, logsBuffer, MAX_MSG_LEN, NULL);

			if (bytes_read == -1) {
				perror("[CommunicationThread] Failed to recieve from LogThread");
			} else {
				strcat(logsBuffer,"\r\n");
				printf(logsBuffer);
				bzero(buffer, 256);
				n = write(newsockfd, logsBuffer, strlen(logsBuffer));
				if (n < 0) 
					error("ERROR writing to socket");
			}
		}
	}
	exit(1);
}

void *doCommunication(void *p) {
	
	/*Lancement du thread de push*/
	pthread_t tPush;
	pthread_create(&tPush, NULL, doPush, NULL);

	/*Création des sockets et mise en place du buffer de communication*/
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

	/*Boucle d'attente de connection*/
	for (;;) {
		listen(sockfd, 5);
		clilen = sizeof (cli_addr);
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

		if (newsockfd < 0)
			error("ERROR on accept");

		/*Boucle de communication en pull pour les commandes du client*/
		for(;;) {
			bzero(buffer, 256);
			n = read(newsockfd, buffer, 255);
			if (n < 0) error("ERROR reading from socket");

			if (!strcmp(buffer, "exit\r\n")) {
				close(newsockfd);
				break;
			}

			if (!strcmp(buffer, "shutdown\r\n")) {
				close(newsockfd);
				close(sockfd);
				return 0;
			}

			n = write(newsockfd, "I got your message\r\n", 20);
			if (n < 0)
				error("ERROR writing to socket");
		}
	}
	return 0;
}