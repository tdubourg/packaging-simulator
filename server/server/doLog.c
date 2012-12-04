#include "doLog.h"
#include "common.h"
#include <stdio.h>

void *doLog(void *p) {
    
    char buffer[MAX_MSG_LEN + 1];
    unsigned int sender;
    int bytes_read;

    mqd_t mboxLogs = mq_open(MBOXLOGS, O_RDWR);
    
    for (;;) {
        
        bytes_read = mq_receive(mboxLogs, buffer, MAX_MSG_LEN, NULL);
        printf("%d",bytes_read);
        if (bytes_read == -1) {
            perror("[MainThread] Failed to recieve");
            //return 0;
        }
        else {
            printf("[MainThread] Data: %s \n", buffer);
            
            
        }
    }

}