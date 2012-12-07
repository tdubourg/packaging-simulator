#include "doControl.h"
#include "common.h"

#ifdef DBG
#include "time.h"
#endif
/*
 * Control thread
 */
void *doControl(void *p)
{
    char msg[MAX_MSG_LEN+1];
	mqd_t mboxControl = mq_open(MBOXCONTROL, O_RDWR);
    
    for (;;)
    {
		// Wait for a command
        // usleep(600000*1000);
        mq_receive(mboxControl, msg, MAX_MSG_LEN, NULL);
        DBG("doControl", "Main", "Received a message");
        DBG("doControl", "Main", msg);
        switch (msg[0])
        {
			// Error case
            case 'E':
                switch (msg[1])
                {
					// Print
                    case 'A':
                        sem_trywait(&SemCtrlBox); // Bloc parts packager
                        break;
					// Palette maker
                    case 'P':
                        sem_trywait(&SemCtrlImp); // Block print
                        break;
					// Warehouse
                    case 'W':
                        sem_trywait(&SemCtrlPallet); // Block palette maker
                        break;
                }
                break;
			// Solving errors
            case 'S':
                switch (msg[1])
                {
					// Print
                    case 'A':
                        sem_trywait(&SemCtrlBox); // Ensure parts packager is blocked
						sem_post(&SemCtrlBox); // Re-launch parts packager
                        break;
					// Palette maker
                    case 'P':
                        sem_trywait(&SemCtrlImp); // Ensure print is blocked
						sem_post(&SemCtrlImp); // Re-launch print
                        break;
					// Warehouse
                    case 'W':
                        sem_trywait(&SemCtrlPallet); // Ensure palette maker is blocked
						sem_post(&SemCtrlPallet); // Re-launch palette maker
                        break;
                }
                break;
        }
    }
}

void stopApplication(){
	// stopping simulation threads
	extern bool needToStop;
	needToStop = TRUE;
	
	mqd_t mBoxPalletStore = mq_open(MBOXPALLETSTORE, O_RDWR);
	mq_send(mBoxPalletStore,STOP_MESSAGE_QUEUE,sizeof(STOP_MESSAGE_QUEUE),1);
	
	// waiting for simulation threads to end
	sleep(1);
	
	// closing Log thread;
	mqd_t mboxLogs = mq_open(MBOXLOGS, O_RDWR);
	mq_send(mboxLogs,STOP_MESSAGE_QUEUE,sizeof(STOP_MESSAGE_QUEUE),1);
	
	// closing Communication thread;
	mqd_t mboxCom = mq_open(MBOXCOMMUNICATION, O_RDWR);
	mq_send(mboxCom,STOP_MESSAGE_QUEUE,sizeof(STOP_MESSAGE_QUEUE),1);
	
	//TODO: close control thread
	
}