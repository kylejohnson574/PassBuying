#ifndef _TRAN_DEF_H_
#define _TRAN_DEF_H_

typedef enum 
{
	BUS,
	SUBWAY,
	COMMUTER_RAIL,
	TANS_TYPE_END

}TRANS_TYPE;

static const char *sTransTypeName [] = 
{
	"BUS",
	"SUBWAY",
	"COMMUTER_RAIL",
	"TRANS_TYPE_END"
};

typedef struct _tans_type_entry_
{
	//type of trans this entry defines
	unsigned short  usTransType;
    unsigned short  usDayMonthlyProRateBegins;
	unsigned short  bVariableRateForLength;
    float           fPerRidePassCosts;
	float           fMonthlyRate;
	float           fPerRideRate;
	float           fPerRideVariableRate;
	float		    fElderlyDiscount;
	float           fStudentDiscount;
	float           fWeekendDiscount;
	float		    fMonthlyProRate;

}TRANS_TYPE_ENTRY;
#endif