#include "doControl.h"
#include "common.h"


void *doControl(void *p)
{
    char msg[256];
	mqd_t mboxControl = mq_open(MBOXCONTROL, O_RDWR);
    
    for (;;)
    {
        mq_receive(&mboxControl, msg, 255, NULL);
        
        switch (msg[0])
        {
            case 'E':
                switch (msg[2])
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
                switch (msg[2])
                {
                    case 'C':
                        sem_post(&SemCtrlImp);
                        break;
                    case 'A':
                        sem_post(&SemCtrlPallet);
                        break;
                }
                break;
            case 'C':
                break;
        }
    }
}
