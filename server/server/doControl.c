#include "doControl.h"
#include "common.h"


void *doControl(void *p)
{
    char msg[MAX_MSG_LEN+1];
	mqd_t mboxControl = mq_open(MBOXCONTROL, O_RDWR);
    
    for (;;)
    {
        mq_receive(&mboxControl, msg, MAX_MSG_LEN, NULL);
        
        switch (msg[0])
        {
            case 'E':
                switch (msg[1])
                {
                    case 'C':
                        sem_trywait(&SemCtrlImp);
                        break;
                    case 'A':
                        sem_trywait(&SemCtrlPallet);
                        break;
                }
                break;
            case 'S':
                switch (msg[1])
                {
                    case 'C':
                        sem_post(&SemCtrlImp);
                        break;
                    case 'A':
                        sem_post(&SemCtrlPallet);
                        break;
                }
                break;
        }
    }
}
