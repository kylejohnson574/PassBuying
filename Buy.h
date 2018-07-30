#ifndef _BUY_H_
#define _BUY_H_

#include "PassBuying\PassBuying\Costs.h"
#include "PassDef.h"

//Function to "buy" a pass which fills out a new per ride pass and 
// inserts it into the Database. 
//  Return true(1) or false(0) depending on sucess 
//  
//  Parameters: 
//    uiTransType            type of transportation this pass is for
//    bIsElderly             is this pass for an elderly person
//    bIsStudent             is this pass for a student
//    ulInputCurrencyAmount  amount of currency to place on pass
//    pcName                 pointer to char with the name of the pass holder
//    ulId                   return value of the pass number assigned to the pass
int buyPerRidePass(unsigned int uiTransType, int bIsElderly, int bIsStudent, float *ulInputCurrencyAmount, char *pcName, unsigned long *ulId);

//Function to get the current costs for a per ride pass
// Return the amount it costs to buy the pass
//  Parameters: 
//    uiTransType            type of transportation this pass is for
//    bIsElderly             is this pass for an elderly person
//    bIsStudent             is this pass for a student
float costsPerRidePass(unsigned int uiTransType, int bIsElderly, int bIsStudent);

//Function to add currency to a per ride pass
//  Return true(1) or false(0) depending on sucess 
//  
//  Parameters: 
//    ulInputCurrencyAmount  amount of currency to place on pass
//    ulId                   return value of the pass number assigned to the pass
//    pEntry                 pointer to entry if known, Pass 0x00 if lookup required
int addCurrencyToPerRidePass(unsigned long ulInputCurrencyAmount, unsigned long ulId, pass *pEntry );

//Function to "buy" a pass which fills out a new monthly pass and 
// inserts it into the Database. 
//  Return true(1) or false(0) depending on sucess 
//  
//  Parameters: 
//    uiTransType            type of transportation this pass is for
//    bIsElderly             is this pass for an elderly person
//    bIsStudent             is this pass for a student
//    pcName                 pointer to char with the name of the pass holder
//    usMonthValidFor        month the pass is valid for
//    usDayBought            day of the month the pass was purchased
//    ulId                   return value of the pass number assigned to the pass
int buyMonthlyPass(unsigned int uiTransType, int bIsElderly, int bIsStudent, char *pcName, unsigned short usMonthValidFor, unsigned short usDayBought, unsigned long *ulId);

//Function to get the current costs for a monthly pass
// Return the amount it costs to buy the pass
//  Parameters: 
//    uiTransType            type of transportation this pass is for
//    bIsElderly             is this pass for an elderly person
//    bIsStudent             is this pass for a student
//    usDayBought            day this pass is being bought on
//    usMonthValidFor        month this pass will be valid for
float costsMonthlyPass(unsigned int uiTransType, int bIsElderly, int bIsStudent, unsigned short usDayBought, unsigned short usMonthValidFor);

//Function to add currency to a per ride pass
//  Return true(1) or false(0) depending on sucess 
//  
//  Parameters: 
//    usDayBought            day this pass is being bought on
//    usMonthValidFor        month this pass will be valid for
//    ulId                   return value of the pass number assigned to the pass
//    pEntry                 pointer to entry if known, Pass 0x00 if lookup required
int renewMonthlyPass(unsigned short usDayBought, unsigned short usMonthValidFor, unsigned long ulId, pass *pEntry );

#endif