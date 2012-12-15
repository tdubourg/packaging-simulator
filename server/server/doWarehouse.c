#include "doWarehouse.h"
#include "common.h"
#include <string.h>
#include <stdlib.h>

void *doWarehouse(void *p)
{
	//**** INIT
	INIT_LOGGER();
	INIT_CHECK_FOR_APP_END();
	extern sem_t SemWarehouse;
	extern batch_type CurrentBatchType;
	extern int AStock, BStock;
	extern pthread_mutex_t LockWarehouseStorageData;

	int storageId = -1;

	//***** MAIN LOOP
	for(;;) {
		DBGPRINT("doWarehouse", "Main", "is unlocked.");
		sem_wait(&SemWarehouse);
		CHECK_FOR_APP_END_AND_STOP("Warehouse");
		DBGPRINT("doWarehouse", "Main", "New palette to store somwhere");
		LOG("doWarehouse: New palette to store somewhere");
		storageId++;

		pthread_mutex_lock(&LockWarehouseStorageData);
		if (CurrentBatchType == BATCH_TYPE_A)
		{
			AStock++;
		} else {
			BStock++;
		}

		pthread_mutex_unlock(&LockWarehouseStorageData);

#define LOG_MSG "doWarehouse: Stored at storageId= %d"
		char* logMessage = (char*)malloc(sizeof(LOG_MSG) + 5);
		sprintf(logMessage, LOG_MSG, storageId);
		LOG(logMessage);
		DBGPRINT("doWarehouse", "Main", "End");
		free(logMessage);
#undef LOG_MSG
		
	}	
}