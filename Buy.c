#include "Buy.h"
#include "PassManager.h"

int buyPerRidePass(unsigned int uiTransType, int bIsElderly, int bIsStudent, float *ulInputCurrencyAmount, char *pcName, unsigned long *ulId)
{
	int ret = 0;
    //Create a generic new pass
    pass *pPass = getGenericPass(uiTransType, bIsElderly, bIsStudent, pcName);

    pay_per_ride_pass *pPerRidePass = getPayPerRidePass();

    if( pPass && pPerRidePass && ulId )
    {
		//Add the currency value amount.
		pPerRidePass->ulCurrentValue = *ulInputCurrencyAmount;

		//Set the type and the pointer to the specific pass
		pPass->ulTypeOfPass = PAY_PER_RIDE;
		pPass->usTransType = uiTransType;
		pPass->pPassData = (void *)pPerRidePass;

		if (addPerRideEntry(pPass))
		{
			*ulId = pPass->ulID;
			ret = 1;
		}
    }

    return ret;
}

float costsPerRidePass(unsigned int uiTransType, int bIsElderly, int bIsStudent)
{
    float fReturn = -1.0;

    TRANS_TYPE_ENTRY *pTransPriceInfo = getCostForTransType(uiTransType);
    
    if( pTransPriceInfo )
    {
        //return the cost of the actually pass 
        fReturn = pTransPriceInfo->fPerRidePassCosts;
    }

	return fReturn;
}

int addCurrencyToPerRidePass(unsigned long ulInputCurrencyAmount, unsigned long ulId, pass *pEntry )
{
	int ret = 0;
    
    if( !pEntry )
    {
		//Pass lookup required
		pEntry = findPerRideEntry(ulId);
    }

	if (pEntry)
	{
		//Verify entry is the correct type of pass
		if ( pEntry->ulTypeOfPass == PAY_PER_RIDE )
		{
			//From the pass get the pay per ride info
			pay_per_ride_pass *pPerRidePass = (pay_per_ride_pass *)pEntry->pPassData;

			if (pPerRidePass != 0)
			{
				//update current value
				pPerRidePass->ulCurrentValue = pPerRidePass->ulCurrentValue + ulInputCurrencyAmount;
				ret = 1;
			}			
		}
	}

    return ret;
}

int buyMonthlyPass(unsigned int uiTransType, int bIsElderly, int bIsStudent, char *pcName, unsigned short usMonthValidFor, unsigned short usDayBought, unsigned long *ulId)
{
	int ret = 0;
	//Create a generic new pass
    pass *pPass = getGenericPass(uiTransType, bIsElderly, bIsStudent, pcName);

    monthly_pass *pMonthlyPass = getMonthlyPass();

    if( pPass && pMonthlyPass && ulId )
    {
		//Set monthly pass variables
		pMonthlyPass->usDayBought = usDayBought;
		pMonthlyPass->usMonthValidFor = usMonthValidFor;

		//Set the type and the pointer to the specific pass
		pPass->ulTypeOfPass = MONTHLY;
		pPass->usTransType = uiTransType;
		pPass->pPassData = (void *)pMonthlyPass;

		if (addMonthlyEntry(pPass))
		{
			*ulId = pPass->ulID;
			ret = 1;
		}
    }    

    return ret;
}

float costsMonthlyPass(unsigned int uiTransType, int bIsElderly, int bIsStudent, unsigned short usDayBought, unsigned short usMonthValidFor)
{
	float fReturn = -1.0;

	TRANS_TYPE_ENTRY *pTransPriceInfo = getCostForTransType(uiTransType);

	if (pTransPriceInfo)
	{
		if (bIsStudent)
		{
			fReturn = pTransPriceInfo->fStudentDiscount * pTransPriceInfo->fMonthlyRate;
		}
		else if (bIsElderly)
		{
			fReturn = pTransPriceInfo->fElderlyDiscount * pTransPriceInfo->fMonthlyRate;
		}
		else if (usDayBought >= pTransPriceInfo->usDayMonthlyProRateBegins)
		{
			fReturn = pTransPriceInfo->fMonthlyProRate * pTransPriceInfo->fMonthlyRate;
		}
		else
		{
			fReturn = pTransPriceInfo->fMonthlyRate;
		}
	}

	return fReturn;
}

int renewMonthlyPass(unsigned short usDayBought, unsigned short usMonthValidFor, unsigned long ulId, pass *pEntry)
{
	int bReturn = 0;

	if (!pEntry)
	{
		//Lookup required. Find entry
		//Search the entries for this Item
		pEntry = findMonthlyEntry(ulId);
	}
	
	if (pEntry)
	{
		//Make sure its a monthly
		if (pEntry->ulTypeOfPass == MONTHLY)
		{
			monthly_pass *pMonthly = (monthly_pass *)pEntry->pPassData;
			if (pMonthly)
			{
				pMonthly->usDayBought = usDayBought;
				pMonthly->usMonthValidFor = usMonthValidFor;
				bReturn = 1;
			}
		}
	}

	return bReturn;
}