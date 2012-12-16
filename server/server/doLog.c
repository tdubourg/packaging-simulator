#include "doLog.h"
#include "common.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <string.h>

/* this theard read messages from log message queue, then send them to communication thread using a message queue.
  This thread also format logs to add time in the begining of each log before writting them in a log file*/
void *doLog(void *p) {

	/* TODO : define message priority and message format to send to communication Thread. */
	/* INIT *******************************************************************/
	char buffer[MAX_MSG_LEN + 1];
	int bytes_read;
	time_t temps;
	struct tm date;

	/* Opening mbox */
	mqd_t mboxLogs = mq_open(MBOXLOGS, O_RDWR);

	mqd_t mboxCom = mq_open(MBOXCOMMUNICATION, O_RDWR | O_NONBLOCK);

	/* MAIN LOOP **************************************************************/
	for(;;) {
		bytes_read = mq_receive(mboxLogs, buffer, MAX_MSG_LEN, NULL); /* @TODO add comment/documentation for this line */
		if (bytes_read == -1) {
			perror("doLog: Failed to receive");
		} else {
			if (!strcmp(buffer, STOP_MESSAGE_QUEUE)) {
				DBGPRINT("doLog", "Main", "Receiving stop message");
				return; /* Ending the thread */
			} else {

				printf("[LogThread] Data: %s %d\n", buffer, bytes_read);
				/* Debug */

				/* Retrieving curent time to insert it into formatted logs. */
				time(&temps);
				date = *localtime(&temps);

				FILE *f = fopen(LOG_FILE_NAME, "a+");

				/* Writing in log file */
				fprintf(f, "[%02d/%02d/%d|%02d:%02d:%02d] %s\n",
						date.tm_mday + 1,
						date.tm_mon + 1,
						date.tm_year + 1900,
						date.tm_hour,
						date.tm_min,
						date.tm_sec,
						buffer);

				fclose(f);

				/* Sending the log message to communication thread using the dedicated message queue. */
				mq_send(mboxCom, buffer, bytes_read, MSG_MEDIUM_PRIORITY); /* @TODO add comment/documentation for this line, especially the use of bytes_read in a *_send() call */

				/* Clearing buffer */
				memset(buffer, 0, bytes_read + 1); /* @TODO comment this line */
			}
		}
	}
}