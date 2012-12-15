#include "doControl.h"
#include "common.h"

#ifdef DBG
#include "time.h"
#include "stdio.h"
#endif

static void stopApplication();
static void parseInitMessage(char* buffer);

/*
 * Control thread
 */
void *doControl(void *p)
{
	INCLUDE(Imp)
	INCLUDE(Palette)
	INCLUDE(Valve)
	INCLUDE(Box)

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
			case ERR:
				// Stop the valve
				SET(Valve, TRUE);
				switch (msg[1])
				{
					// Print
					case PRINT:
						// Block parts packager
						SET(Box, TRUE);
						break;
					// Palette maker
					case PALETTE:
						// Block print
						SET(Imp, TRUE);
						break;
					// Warehouse
					case WAREHOUSE:
						// Block palette maker
						SET(Palette, TRUE);
						break;
				}
				break;
			// Solving errors
			case SOLVE:
				switch (msg[1])
				{
					// Print
					case PRINT:
						// Block parts packager
						SET(Box, FALSE);
						break;
					// Palette maker
					case PALETTE:
						// Block print
						SET(Imp, FALSE);
						break;
					// Warehouse
					case WAREHOUSE:
						// Block palette maker
						SET(Palette, FALSE);
						break;
				}
				break;
			// Relaunch all tasks (after an urgent stop)
			case 'R':
				SET(Box, FALSE);
				SET(Palette, FALSE);
				SET(Imp, FALSE);
				SET(Valve, FALSE);
				break;
			// Stop app
			case 'Q':
				SET(Valve, TRUE);
				stopApplication();
				//stopping this thread;
				return;
				
				break;
				
			case 'I':
				parseInitMessage(msg);
				break;
			
		}
	}
}

static void parseInitMessage(char* buffer){
	char* ptr,res;
	res = strtok_r(buffer,'-',ptr);
	printf("%s :\n",res);
	printf("lolilol\n");
	while(res!=NULL){
		printf("%s :\n",res);
		res = strtok_r(buffer,'-',ptr);
	}
	return;
}

static void stopApplication(){
	// stopping simulation threads
	extern bool needToStop;
	mqd_t mboxPalletStore = mq_open(MBOXPALLETSTORE, O_RDWR);
	mqd_t mboxLogs = mq_open(MBOXLOGS, O_RDWR);
	mqd_t mboxCom = mq_open(MBOXCOMMUNICATION, O_RDWR);
	needToStop = TRUE;
	
	mq_send(mboxPalletStore, STOP_MESSAGE_QUEUE, sizeof(STOP_MESSAGE_QUEUE), MSG_LOW_PRIORITY);
	
	// waiting for simulation threads to end
	sleep(1);
	
	// closing Log thread;
	mq_send(mboxLogs,STOP_MESSAGE_QUEUE, sizeof(STOP_MESSAGE_QUEUE),MSG_LOW_PRIORITY);
	
	// closing Communication thread;
	mq_send(mboxCom,STOP_MESSAGE_QUEUE, sizeof(STOP_MESSAGE_QUEUE), MSG_LOW_PRIORITY);
	
	//TODO: close control thread
	
}
