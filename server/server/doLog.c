#include "doLog.h"
#include "common.h"
#include <stdio.h>

void *doLog(void *p) {
    
    char buffer[MAX_MSG_LEN + 1];
    unsigned int sender;
    int bytes_read;
    bool keepRunning = TRUE;

    //opening mbox
    mqd_t MboxLogs = mq_open(MBOX_LOG_NAME, O_RDWR );
    
    //opening file
    FILE *f = fopen(LOG_FILE_NAME, "wb");
    
    while(keepRunning) {
        
        bytes_read = mq_receive(MboxLogs, buffer, MAX_MSG_LEN, NULL);
        printf("%d",bytes_read);
        if (bytes_read == -1) {
            perror("[MainThread] Failed to recieve");
            //return 0;
        }
        else {
            printf("[MainThread] Data: %s \n", buffer);
            
            fwrite(buffer, bytes_read, 1, f);
            
        }
    }
    fclose(f);

}