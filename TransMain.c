#include "TransMain.h"
#include "Buy.h"
#include "PassManager.h"

unsigned short initMain(TRANS_TYPE _transType)
{
	initManager();
	TransType = _transType;
	pCurrentPass = 0;
	return 1;
}

void unInit()
{
	destroy();
}

unsigned short findId(unsigned long *Id)
{
	unsigned short bReturn = 0;
	//Current Id pointer is correct
	if (Id)
	{
		// Is a monthly pass
		if (*Id & 0x1)
		{
			pCurrentPass = findMonthlyEntry( *Id);
		}
		else
		{
			// Is a Per Ride Pass
			pCurrentPass = findPerRideEntry( *Id);
		}
		//Was the entry found
		if (pCurrentPass)
		{
			bReturn = 1;
		}
	}

	return bReturn;
}

// Get the type of pass from the cached pass
unsigned short getPassType(unsigned long *Id, PASS_TYPE *type)
{
	unsigned short bReturn = 0;
	if ((type) && (Id) && findId(Id))
	{
		// This should be true after a find
		if (pCurrentPass)
		{
			//Make sure the pass is the same one
			if (pCurrentPass->ulID == *Id)
			{
				*type = pCurrentPass->ulTypeOfPass;
				bReturn = 1;
			}
		}
	}

	return bReturn;
}

unsigned short buyPass(PASS_TYPE *type, unsigned long *Id, float moneyIn, float *moneyOut, buy_pass_info *info)
{
	unsigned short bReturn = 0;

	float priceForPass = getPriceOfPass(type, info);

	// A price was found for this type
	// and info is a valid pointer
	if ((priceForPass != -1.0) && info )
	{
		//Calculate money left
		*moneyOut = moneyIn - priceForPass;

		//There is not enough money return false and show how much is missing.
		if (*moneyOut < 0.0)
		{
			return bReturn;
		}

		//There is enough money so buy pass
		if ((*type) == PAY_PER_RIDE)
		{
			bReturn = buyPerRidePass(TransType, info->bIsElderly, info->bIsStudent, moneyOut, info->pcName, Id);
			//All extra money is added to pass
			*moneyOut = 0;
		}
		else
		{
			bReturn = buyMonthlyPass(TransType, info->bIsElderly, info->bIsStudent, info->pcName, info->usMonthValidFor, info->usDayBought, Id);
		}
	}

	return bReturn;
}

// Get price for pass of a certain type
float getPriceOfPass(PASS_TYPE *type, buy_pass_info *info)
{
	float fReturn = -1.0;
	if (type && info)
	{
		if (*type == PAY_PER_RIDE)
		{
			fReturn = costsPerRidePass(TransType, info->bIsElderly, info->bIsStudent);
		}
		else
		{
			fReturn = costsMonthlyPass(TransType, info->bIsElderly, info->bIsStudent, info->usDayBought, info->usMonthValidFor);
		}
	}
	return fReturn;
}

unsigned short getRenewPrice(unsigned long *Id, PASS_TYPE *type, float *price, unsigned short usDayBought, unsigned short usMonthValidFor)
{
	unsigned short bReturn = 0;
	if ((Id) && (type) && (price) && findId(Id))
	{
		// This should be true after a find
		if (pCurrentPass)
		{
			*price = costsMonthlyPass(TransType, pCurrentPass->bIsElderly, pCurrentPass->bIsStudent, usDayBought, usMonthValidFor);
			bReturn = 1;
		}
	}

	return bReturn;
}

// Add money to a per ride pass
unsigned short addCurrencyToPass(unsigned long *Id, float moneyIn)
{
	unsigned short bReturn = addCurrencyToPerRidePass(moneyIn, *Id, 0x00);
	return bReturn;
}

// Renew a monthly pass
unsigned short renewPass(unsigned long *Id, unsigned short usDayBought, unsigned short usMonthValid, float moneyIn, float *moneyOut)
{
	unsigned short bReturn = 0;
	if ( (Id) && ((pCurrentPass->ulID == *Id) || (findId(Id))) )
	{
		// This should be true after a find
		if (pCurrentPass)
		{
			//Make sure the pass is the same one
			if ((pCurrentPass->ulID == *Id) && moneyOut && (pCurrentPass->ulTypeOfPass == MONTHLY))
			{
				//Get the cost for a monthly pass
				float cost = costsMonthlyPass(TransType, pCurrentPass->bIsElderly, pCurrentPass->bIsStudent, usDayBought, usMonthValid);
				
				//make sure there is enough money
				*moneyOut = moneyIn - cost;
				if(*moneyOut < 0.0)
				{
					*moneyOut = moneyIn;
					return bReturn;
				}
				else
				{
					//There is enough money so buy the pass
					renewMonthlyPass(usDayBought, usMonthValid, *Id, pCurrentPass);
					bReturn = 1;
				}
			}
		}
	}

	return bReturn;
}

float getPerRidePrice(unsigned long *Id, unsigned short bIsWeekend)
{
	float fReturn = -1.0;
	if (findId(Id))
	{
		// This should be true after a find
		if (pCurrentPass)
		{
			//Make sure the pass is the same one
			if (pCurrentPass->ulID == *Id)
			{
				fReturn = pricePerRide(*Id, TransType, bIsWeekend, 0);
			}
		}
	}
	return fReturn;
}

// Use a per ride pass
unsigned short usePerRide(unsigned long *Id, unsigned short bIsWeekend)
{
	unsigned int ret = 0;
	if (pCurrentPass && Id)
	{
		if (pCurrentPass->ulID == *Id)
		{
			ret = usePerRidePass(*Id, TransType, bIsWeekend, 0, pCurrentPass);
		}
		else
		{
			ret = usePerRidePass(*Id, TransType, bIsWeekend, 0, 0);
		}
	}
	return ret;
}

// Use monthly ride pass
unsigned short useMonthly(unsigned long *Id, unsigned short dayOfRide, unsigned short monthOfUse)
{
	unsigned int ret = 0;
	if (pCurrentPass && Id)
	{
		if (pCurrentPass->ulID == *Id)
		{
			ret = useMonthlyPass(*Id, TransType, dayOfRide, monthOfUse, pCurrentPass);
		}
		else
		{
			ret = useMonthlyPass(*Id, TransType, dayOfRide, monthOfUse, 0x00);
		}
	}
	return ret;
}

unsigned short checkPassBalance(unsigned long *Id, float *balance)
{
	return checkPerRideBalancePass(*Id, balance);
}

unsigned short checkMonthlyValid(unsigned long *Id, unsigned short *bValid, unsigned short *usMonth)
{
	return checkMonthlyPassValid(*Id, bValid, usMonth);
}

pass *debugGetMonthly()
{
	return getNextMonthlyEntry();
}

pass *debugGetPerRide()
{
	return getNextPerRideEntry();
}
