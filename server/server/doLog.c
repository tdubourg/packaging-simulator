#include "doLog.h"
#include "common.h"
#include <stdio.h>
#include <unistd.h>
#include <time.h>

void *doLog(void *p) {

    //TODO : define message priority and message format to send to communication Thread.
    
    char buffer[MAX_MSG_LEN + 1];
    unsigned int sender;
    int bytes_read;
    bool keepRunning = TRUE;
    time_t temps;
    struct tm date;


    //opening mbox
    mqd_t mboxLogs = mq_open(MBOXLOGS, O_RDWR);
    
    mqd_t mboxCom = mq_open(MBOXCOMMUNICATION, O_RDWR);

    while (keepRunning) {
        bytes_read = mq_receive(mboxLogs, buffer, MAX_MSG_LEN, NULL);//@TODO comment this line
        //printf("%d", bytes_read);
        if (bytes_read == -1) {
            perror("[LogThread] Failed to recieve");
            //return 0;
        } else {
            printf("[LogThread] Data: %s %d\n", buffer, bytes_read);
            //debug

            // retrieving curent time to insert it into formated logs.
            time(&temps);
            date = *localtime(&temps);

            //TODO : keep file and close it once thread end is handled
            FILE *f = fopen(LOG_FILE_NAME, "a+");
            //writting in logg file
            fprintf(f, "[%02d/%02d/%d|%02d:%02d:%02d] %s\n",
                    date.tm_mday + 1,
                    date.tm_mon + 1,
                    date.tm_year + 1900,
                    date.tm_hour,
                    date.tm_min,
                    date.tm_sec,
                    buffer);
            fclose(f);

            //sending the log message to communication thread using the dedicated message queue.
            mq_send(mboxCom,buffer,bytes_read,1);//@TODO comment this line
            
            // clearing buffer
            memset(buffer, 0, bytes_read + 1);//@TODO comment this line
        }
    }

}