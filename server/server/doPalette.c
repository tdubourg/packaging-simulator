#include "doPalette.h"
#include "common.h"

void *doPalette(void *p)
{
	INCLUDE(Palette)
	INCLUDE_INTEGER(PrintPaletteQueue)
	extern int BOXES_BY_PALETTE;
	extern sem_t SemSyncImpPalette;
    int currentPaletteBoxesNumber = 0;
	
	//**** INIT
	// Opening message queue
	mqd_t mboxControl = mq_open(MBOXCONTROL, O_RDWR);
	
    for(;;) {
		sem_wait(&SemSyncImpPalette);
		pthread_mutex_lock(&LockPrintPaletteQueue);
		while (PrintPaletteQueueValue <= 0) { /* We're paused */
			pthread_cond_wait(&CondPrintPaletteQueue, &LockPrintPaletteQueue); /* Wait for play signal */
		}
		DBG("doPalette", "Main", "New box added in palette");
        --PrintPaletteQueueValue;
		currentPaletteBoxesNumber = (currentPaletteBoxesNumber + 1) % BOXES_BY_PALETTE;
		pthread_cond_signal(&CondPrintPaletteQueue);
		pthread_mutex_unlock(&LockPrintPaletteQueue);
		
        sem_post(&SemSyncImpPalette);
	}
}