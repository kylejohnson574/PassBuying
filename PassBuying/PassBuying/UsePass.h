#ifndef __USE_PASS_H__
#define __USE_PASS_H__

#include "../../PassDef.h"

//Function to use the per ride pass
// Return if was successful or not
//  Parameters: 
//    ulId                   return value of the pass number assigned to the pass
//    uiTransType            type of transportation this pass is for
//    bIsWeekend             boolean of wither the day is a weekend
//    ulLength               length of trip if using a variable pricing scheme
//    pEntry                 pointer to pass if already known, 0x00 if a lookup needed 
extern int usePerRidePass(unsigned long ulId, unsigned int uiTransType, int bIsWeekend, unsigned long ulLength, pass *pEntry);

//Function to return the costs of a per ride 
// Return if was successful or not
//  Parameters: 
//    ulId                   return value of the pass number assigned to the pass
//    uiTransType            type of transportation this pass is for
//    bIsWeekend             boolean of wither the day is a weekend
//    ulLength               length of trip if using a variable pricing scheme				 
extern float pricePerRide(unsigned long ulId, unsigned int uiTransType, int bIsWeekend, unsigned long ulLength);

//Function to use the monthly pass
// Return if was successful or not
//  Parameters: 
//    ulId                   return value of the pass number assigned to the pass
//    uiTransType            type of transportation this pass is for
//    usDayOfRide            day of the ride
//    usMonthOfRide          month of the ride
//    pEntry                 pointer to pass if already known, 0x00 if a lookup needed
extern int useMonthlyPass(unsigned long ulId, unsigned int uiTransType, unsigned short usDayOfRide, unsigned short usMonthOfRide, pass *pEntry);

//Function to check balance of Per Ride Pass
// Return if was successful or not
//  Parameters: 
//    ulId                   pass number assigned to the pass
//    pfBalance              return float value of per ride balance
extern int checkPerRideBalancePass(unsigned long ulId, float *bfBalance);
//Function to check balance of Per Ride Pass
// Return if was successful or not
//  Parameters: 
//    ulId                   pass number assigned to the pass
//    bIsValid               return if pass is valid
//    usMonthValid           return month the pass expires
extern int checkMonthlyPassValid(unsigned long ulId, unsigned short *bIsValid, unsigned short *usMonthValid );
#endif //__USE_PASS_H__