#include "doPalette.h"
#include "common.h"

void *doPalette(void *p)
{
	extern int BOXES_BY_PALETTE;
	INCLUDE(Palette)
	extern int BOXES_QUEUE;
	extern sem_t SemSyncImpPalette;
    int currentPaletteBoxesNumber = 0;
	
	//**** INIT
	// Opening message queue
	mqd_t mboxControl = mq_open(MBOXCONTROL, O_RDWR);
	
    for(;;) {
		sem_wait(&SemSyncImpPalette);
		pthread_mutex_lock(&LockPalette);
		while (BOXES_QUEUE <= 0) { /* We're paused */
			pthread_cond_wait(&CondPalette, &LockPalette); /* Wait for play signal */
		}
		DBG("doPalette", "Main", "New box added in palette");
        --BOXES_QUEUE;
		currentPaletteBoxesNumber = (currentPaletteBoxesNumber + 1) % BOXES_BY_PALETTE;
		pthread_cond_signal(&CondPalette);
		pthread_mutex_unlock(&LockPalette);
		
        sem_post(&SemSyncImpPalette);
	}
}