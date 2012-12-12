#include "doWarehouse.h"
#include "common.h"

void *doWarehouse(void *p)
{
	//**** INIT
	INIT_LOGGER();
	extern sem_t SemWarehouse;
	extern batch_type CurrentBatchType;
	extern int AStock, BStock;
	extern pthread_mutex_t LockWarehouseStorageData;

	int storageId = -1;

	//***** MAIN LOOP
	for(;;) {
		DBG("doWarehouse", "Main", "is unlocked.");
		sem_wait(&SemWarehouse);
		DBG("doWarehouse", "Main", "New palette to store somwhere");
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


		LOG("doWarehouse: Stored at storageId=");
		LOG(storageId);
		DBG("doWarehouse", "Main", "End");

		
	}	
}