#include "doPalette.h"
#include "common.h"

void *doPalette(void *p)
{
	INCLUDE(Palette)
	extern int BOXES_BY_PALETTE;
	extern pthread_mutex_t paletteLock;
	extern pthread_cond_t paletteCond;
	extern int BoxesQueue;
	extern sem_t SemSyncImpPalette;
    int currentPaletteBoxesNumber = 0;
	
	//**** INIT
	// Opening message queue
	mqd_t mboxControl = mq_open(MBOXCONTROL, O_RDWR);
	
    for(;;) {
		sem_wait(&SemSyncImpPalette);
		pthread_mutex_lock(&paletteLock);
		while (BoxesQueue <= 0) { /* We're paused */
			pthread_cond_wait(&paletteCond, &paletteLock); /* Wait for play signal */
		}
		DBG("doPalette", "Main", "New box added in palette");
        --BoxesQueue;
		currentPaletteBoxesNumber = (currentPaletteBoxesNumber + 1) % BOXES_BY_PALETTE;
		pthread_cond_signal(&paletteCond);
		pthread_mutex_unlock(&paletteLock);
		
        sem_post(&SemSyncImpPalette);
	}
}