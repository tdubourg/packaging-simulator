void partsPackager(void*) {
	extern int PARTS_BY_BOX;
	extern semt_t* semSyncBoxImp;
	
	int currentBoxPartsNumber = 0;
	//**** INIT
	


	//**** MAIN LOOP
	for (;;) {
		//**** SYNC SEMAPHORE CHECK

		//* There's a new part to put in that freaking box:
		currentBoxPartsNumber = (currentBoxPartsNumber + 1) % PARTS_BY_BOX;

		if (!currentBoxPartsNumber) //* Is the box full?
		{
			//**** "READY TO GO TO PRINTER" SEMAPHORE CHECK
			sem_wait(semSyncBoxImp);
		}

	}


	/**** END / CLEANING 
}
