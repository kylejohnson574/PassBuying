#include "TransDef.h"
#include "PassManager.h"
#include "Costs.h"
#include "UsePass.h"

int usePerRidePass(unsigned long ulId, unsigned int uiTransType, int bIsWeekend, unsigned long ulLength, pass *pEntry)
{
	pEntry = findPerRideEntry(ulId);

	float totalCosts = 0.0;
	int bReturn = 0;

	// Entry found and it must match type
	if ( pEntry && (pEntry->usTransType == uiTransType) )
	{
		//Get the per ride pass from the generic pass
		pay_per_ride_pass *pRide = (pay_per_ride_pass *)pEntry->pPassData;
		
		totalCosts = pricePerRide(ulId, uiTransType, bIsWeekend, ulLength);

		// Take the determined costs and see if there
		// is enough money on the pass.
		if (totalCosts <= pRide->ulCurrentValue)
		{
			//Take out the money and return true
			pRide->ulCurrentValue = (unsigned long)(pRide->ulCurrentValue - totalCosts);
			bReturn = 1;
		}
	}

	return bReturn;
}

float pricePerRide(unsigned long ulId, unsigned int uiTransType, int bIsWeekend, unsigned long ulLength)
{
	pass *pEntry = 0;
	pEntry = findPerRideEntry(ulId);

	float totalCosts = -1.0;
	int bReturn = 0;
	float currentDiscount = 0.0;

	// Entry found and it must match type
	if (pEntry && pEntry->usTransType == uiTransType)
	{
		//Get the per ride pass from the generic pass
		pay_per_ride_pass *pRide = (pay_per_ride_pass *)pEntry->pPassData;

		//Now get the pricing info for the trans type
		TRANS_TYPE_ENTRY *pTransPriceInfo = getCostForTransType(uiTransType);

		if (pTransPriceInfo)
		{
			// Does this support pricing for variable length
			if (pTransPriceInfo->bVariableRateForLength)
			{
				totalCosts = pTransPriceInfo->fPerRideVariableRate * ulLength;
			}
			else
			{
				totalCosts = pTransPriceInfo->fPerRideRate;
			}
			//If it is a weekend then factor in the discount
			if (bIsWeekend)
			{
				currentDiscount = pTransPriceInfo->fWeekendDiscount;
			}
			else
			{
				//Check for elderly and student. 
				// Take the best discount avaible to the current passholder
				if (pEntry->bIsElderly)
				{
					if (pTransPriceInfo->fElderlyDiscount > currentDiscount)
					{
						currentDiscount = pTransPriceInfo->fElderlyDiscount;
					}
				}

				if (pEntry->bIsStudent)
				{
					if (pTransPriceInfo->fStudentDiscount > currentDiscount)
					{
						currentDiscount = pTransPriceInfo->fStudentDiscount;
					}
				}
			}

			//factor in discount
			if (currentDiscount != 0.0)
			{
				totalCosts = totalCosts * currentDiscount;
			}
		}
	}

	return totalCosts;
}



int useMonthlyPass(unsigned long ulId, unsigned int uiTransType, unsigned short usDayOfRide, unsigned short usMonthOfRide, pass *pEntry)
{
	int bReturn = 0;
	
	//Lookup required
	if (!pEntry)
	{
		pEntry = findPerRideEntry(ulId);
	}

	// Entry found and it must match type
	if (pEntry && (pEntry->usTransType == uiTransType) && (pEntry->bIsValid) )
	{
		//Get the monthly pass from the generic pass
		monthly_pass *pMonthly = (monthly_pass *)pEntry->pPassData;

		if ((pMonthly)&& (pMonthly->usMonthValidFor == usMonthOfRide))
		{
			bReturn = 1;
		}
	}

	return bReturn;
}

int checkPerRideBalancePass(unsigned long ulId, float *bfBalance)
{
	int ret = 0;
	pass *pEntry = findPerRideEntry(ulId);
	
	if (pEntry)
	{
		if (bfBalance && (pEntry->ulTypeOfPass == PAY_PER_RIDE))
		{
			pay_per_ride_pass* pPass = (pay_per_ride_pass *)pEntry->pPassData;
			if (pPass)
			{
				*bfBalance = (float)pPass->ulCurrentValue;
				ret = 1;
			}
		}
	}

	return ret;
}

int checkMonthlyPassValid(unsigned long ulId, unsigned short *bIsValid, unsigned short *usMonthValid)
{
	int ret = 0;
	pass *pEntry = findMonthlyEntry(ulId);

	if (pEntry)
	{
		if (bIsValid && usMonthValid && (pEntry->ulTypeOfPass == MONTHLY))
		{
			monthly_pass* pPass = (monthly_pass *)pEntry->pPassData;
			if (pPass)
			{
				*bIsValid     = pEntry->bIsValid;
				*usMonthValid = pPass->usMonthValidFor;
				ret = 1;
			}
		}
	}

	return ret;
}
