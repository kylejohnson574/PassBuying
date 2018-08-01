#ifndef _TRANS_MAIN_H
#define _TRANS_MAIN_H
#include "PassManager.h"
#include "PassDef.h"
#include "TransDef.h"
#include "Costs.h"
#include "UsePass.h"

//The type of transportation this instance if for
//the types are defined TransDef.h
TRANS_TYPE TransType;

//The cached pointer to the current pass
pass *pCurrentPass;

//A struct to hold basic info for buying a pass
typedef struct buy_pass_info_t_
{
	char *pcName;
	unsigned short ulTypeOfPass;
	unsigned short bIsStudent;
	unsigned short bIsElderly;
	unsigned short usMonthValidFor;
	unsigned short usDayBought;
} buy_pass_info;

// Called to setup the main program
unsigned short initMain(TRANS_TYPE _transType);

// Called to start a shutdown
void unInit();

// ---------------- Finding a current pass ---------------
// Called to find and cache an ID
unsigned short findId(unsigned long *Id);

// Get the type of pass from the cached pass
unsigned short getPassType(unsigned long *Id, PASS_TYPE *type);

// ----------------- Buying Pass, adding money, or renewing -----------
// Buy a new pass 
unsigned short buyPass(PASS_TYPE *type, unsigned long *Id, float moneyIn, float *moneyOut, buy_pass_info *info);

// Get price for pass of a certain type
float getPriceOfPass(PASS_TYPE *type, buy_pass_info *info);

// Add money to a per ride pass
unsigned short addCurrencyToPass(unsigned long *Id, float moneyIn);

//Get money for renewing price
unsigned short getRenewPrice(unsigned long *Id, PASS_TYPE *type, float *price, unsigned short usDayBought, unsigned short usMonthValidFor);

// Renew a monthly pass
unsigned short renewPass(unsigned long *Id, unsigned short usDayBought, unsigned short usMonthValid, float moneyIn, float *moneyOut);

// ----------------- Using the pass -----------
// Get route price for a per ride pass
float getPerRidePrice(unsigned long *Id, unsigned short bIsWeekend);

// Use a per ride pass
unsigned short usePerRide(unsigned long *Id, unsigned short bIsWeekend);

// Use monthly ride pass
unsigned short useMonthly(unsigned long *Id, unsigned short dayOfRide, unsigned short monthOfUse);

// Check how much is left on a pass
unsigned short checkPassBalance(unsigned long *Id, float *balance);

// Check monthly pass
unsigned short checkMonthlyValid(unsigned long *Id, unsigned short *bValid, unsigned short *usMonth);

//------------------- Debug Queue ---------------
pass *debugGetMonthly();
pass *debugGetPerRide();
#endif
