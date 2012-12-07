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
						// Block parts packager
						SET(Box, TRUE);
						break;
					// Palette maker
					case 'P':
						// Block print
						SET(Imp, TRUE);
						break;
					// Warehouse
					case 'W':
						// Block palette maker
						SET(Palette, TRUE);
						break;
				}
				break;
			// Solving errors
			case 'S':
				switch (msg[1])
				{
					// Print
					case 'A':
						// Block parts packager
						SET(Box, FALSE);
						break;
					// Palette maker
					case 'P':
						// Block print
						SET(Imp, FALSE);
						break;
					// Warehouse
					case 'W':
						// Block palette maker
						SET(Palette, FALSE);
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
