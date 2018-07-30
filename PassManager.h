#ifndef _PASS_MANAGER_H_
#define _PASS_MANAGER_H_
#include "PassQueue.h"

/*
	Pass Manager is the communication layer to the backend.
	This class is here so that all the other code above can 
	remain unchanged no matter how the passes are stored. It 
	doesn't matter if there is a DB or a network connection.
*/

pass_queue *monthly_queue;
pass_queue *perRide_queue;

unsigned long perRideId;
unsigned long perMonthlyId;

extern void initManager();
extern pass *findMonthlyEntry(unsigned long id);
extern pass *findPerRideEntry(unsigned long id);

extern int addMonthlyEntry(pass* pass);
extern int addPerRideEntry(pass* pass);

extern pass *getGenericPass(unsigned int uiTransType, int bIsElderly, int bIsStudent, char *pcName);
extern pay_per_ride_pass *getPayPerRidePass();
extern monthly_pass *getMonthlyPass();

extern pass *getNextMonthlyEntry();
extern pass *getNextPerRideEntry();

extern void removeMonthlyEntry(unsigned long id);
extern void removePerRideEntry(unsigned long id);

extern unsigned long getNextMonthlyId();
extern unsigned long getNextPerRideId();
#endif