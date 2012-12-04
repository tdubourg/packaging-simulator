#include "doControl.h"
#include "common.h"

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
        mq_receive(&mboxControl, msg, MAX_MSG_LEN, NULL);
        
        switch (msg[0])
        {
			// Error case
            case 'E':
                switch (msg[1])
                {
					// Parts packager
                    case 'C':
                        sem_trywait(&SemCtrlImp); // Block print
                        break;
					// Print
                    case 'A':
                        sem_trywait(&SemCtrlPallet); // Bloc palette maker
                        break;
                }
                break;
			// Solving case
            case 'S':
                switch (msg[1])
                {
					// Parts packager
                    case 'C':
						sem_trywait(&SemCtrlImp); // Ensure print is blocked
                        sem_post(&SemCtrlImp); // Re-run print
                        break;
					// Print
                    case 'A':
						sem_trywait(&SemCtrlPallet); // Ensure palette maker is blocked
                        sem_post(&SemCtrlPallet); // Re-run palette maker
                        break;
                }
                break;
        }
    }
}
