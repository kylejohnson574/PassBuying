#ifndef _COSTS_H_
#define _COSTS_H_
#include "../../TransDef.h"

//Function to get the current costs for type of transportation
// Return the cost data for that transportation type
//  Parameters: 
//    uiTransType            type of transportation this pass is for

extern TRANS_TYPE_ENTRY *getCostForTransType(unsigned int uiTransType);

#endif