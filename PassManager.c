#include "PassManager.h"
#include <stdlib.h>
/*
	This implementation of the backend is just a basic
	queue system that holds the added passes. That is 
	why initManager() sets up queues. Later this can 
	be used to setup a connection of some type. Also 
	the unique identifier in this system at the moment
	is the ID. Assuming that a pass will hold some type
	of barcode ID that will be used to determine which 
	pass is being referenced.
*/

//Save pass pointer's for the current malloc
//This is so if an add failed they can be freed
//On real hardware this will need to be down 
//however communication will be setup.
pass *currentPassPointer;
pay_per_ride_pass *currentPayPerRidePass;
monthly_pass *currentMonthlyPass;

//Function to get a location to store a new pass.
//On a real system this could be handled a lot of different ways including
//static memory locations. If there is a communication to a remote DB
//then more than likely only one pass will be needed as a cache location
pass *getGenericPass(unsigned int uiTransType, int bIsElderly, int bIsStudent, char *pcName)
{
	pass *pPass = (pass *)malloc(sizeof(pass));
	if (pPass && pcName)
	{
		pPass->bIsElderly = bIsElderly;
		pPass->bIsStudent = bIsStudent;
		pPass->pcName = pcName;
		pPass->bIsValid = 1;
	}

	currentPassPointer = pPass;

	return pPass;
}

pay_per_ride_pass *getPayPerRidePass()
{
	currentPayPerRidePass = (pay_per_ride_pass *)malloc(sizeof(pay_per_ride_pass));
	currentMonthlyPass = 0;
	return currentPayPerRidePass;
}

monthly_pass *getMonthlyPass()
{
	currentPayPerRidePass = 0;
	currentMonthlyPass = (monthly_pass *)malloc(sizeof(monthly_pass));
	return currentMonthlyPass;
}

void initManager()
{
	monthly_queue = initQueue();
	perRide_queue = initQueue();

    perRideId = 1;
    perMonthlyId = 1;
}

pass *findMonthlyEntry( unsigned long id)
{
	return findPass(monthly_queue, id);
}

pass *findPerRideEntry( unsigned long id)
{
	return findPass(perRide_queue, id);
}

int addMonthlyEntry(pass* pass)
{
	int ret = 0;
	if (pass)
	{
		//Assign an ID and make sure it is valid
		pass->ulID = getNextMonthlyId();
		if (pass->ulID != 0)
		{
			//Got a valid ID so add to queue
			if (addItem(monthly_queue, pass))
			{
				perRideId++;
				ret = 1;
			}
		}

		//An issue adding so free memory since the above won't
		if (!ret)
		{
			free(currentPassPointer);
			if (currentMonthlyPass)
			{
				free(currentMonthlyPass);
			}
		}
	}

	return ret;
}
int addPerRideEntry(pass* pass)
{
	int ret = 0;
	if (pass)
	{
		//Assign an ID and make sure it is valid
		pass->ulID = getNextPerRideId();
		if (pass->ulID != 0)
		{
			//Got a valid ID so add to queue
			if (addItem(perRide_queue, pass))
			{
				perRideId++;
				ret = 1;
			}
		}

		//An issue adding so free memory since the above won't
		if (!ret)
		{
			free(currentPassPointer);
			if (currentPayPerRidePass)
			{
				free(currentPayPerRidePass);
			}
		}
	}
	
    return ret;
}

pass *getNextMonthlyEntry()
{
	return getNext(monthly_queue);;
}
pass *getNextPerRideEntry()
{
	return getNext(perRide_queue);
}

void removeMonthlyEntry(unsigned long id)
{
	removeItem(monthly_queue, id);
}

void removePerRideEntry(unsigned long id)
{
	removeItem(perRide_queue, id);
}

unsigned long getNextMonthlyId()
{
	unsigned long ul;
	ul = ((perMonthlyId << 1) | 1);
    return ul;
}

unsigned long getNextPerRideId()
{
	unsigned long ul;
	ul = ((perMonthlyId << 1));
    return ul;
}

void destroy()
{
	pass *pCurrent = getNextMonthlyEntry();
        while( pCurrent )
	{
		removeMonthlyEntry(pCurrent->ulID);
		pCurrent = getNextMonthlyEntry();
	}
	
	pCurrent = getNextPerRideEntry();
	while( pCurrent )
	{
		removePerRideEntry(pCurrent->ulID);
		pCurrent = getNextPerRideEntry();
	}
	
	if( monthly_queue )
	{
		free(monthly_queue);
	}
	if( perRide_queue )
	{
		free(perRide_queue);
	}
}
