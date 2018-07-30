#ifndef __PASS_DEF_H_
#define __PASS_DEF_H_

typedef struct pass_t_
{
	unsigned short bIsValid;
	unsigned long ulID;
	unsigned short usTransType;
	char *pcName;	
	unsigned short ulTypeOfPass;
	void *pPassData;
	unsigned short bIsStudent;
	unsigned short bIsElderly;
} pass;
typedef struct monthly_pass_t_
{
	unsigned short usMonthValidFor;
	unsigned short usDayBought;
	
} monthly_pass;

typedef struct pay_per_ride_pass_t_ 
{
	unsigned long ulCurrentValue;
} pay_per_ride_pass;

// A enum for the types of passes
typedef enum
{
	PAY_PER_RIDE,
	MONTHLY,
	PASS_TYPE_END
}PASS_TYPE;

#endif
