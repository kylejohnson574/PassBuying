// PassBuying.cpp : Defines the entry point for the console application.
//

#include "TransMain.h"

#include <stdio.h>

char names[10][50];
unsigned int number = 0;
unsigned int current_id = 0;

char getElderlyStatus(unsigned char age)
{
	return (age > 64);
}

void init()
{
	unsigned short input = 0;
	printf("---------- Welcome ----------------\n");
	printf("  Init the console\n");
	for (int i = 0; i < TANS_TYPE_END; i++)
	{
		printf("%i : %s\n", i ,sTransTypeName[i] );
	}
	printf( "  Please enter the transportation type: \n");
	scanf("%hi", &input);

	initMain((TRANS_TYPE)input);
}

unsigned short isValidPass(unsigned long *id, PASS_TYPE *desiredType)
{
	unsigned short rt = 0;
	PASS_TYPE type;
	if (getPassType(id, &type))
	{
		if (*desiredType == type)
		{
			rt = 1;
		}
		else
		{
			printf("Sorry Pass %li is not the correct type of pass\n", *id);
		}
	}
	else
	{
		printf("Sorry Pass %li is not a valid Pass\n", *id);
	}

	return rt;
}

void getInputData(buy_pass_info *info)
{
	char resp = 0x00;
	char n = 0x00;
	unsigned short age = 0;
	printf("Age: ");
	scanf("%hi", &age);
	scanf("%c", &n);

	info->bIsElderly = getElderlyStatus(age);
	do
	{
		printf("Student(y/n): ");
		scanf("%c", &resp);
		printf("\n");
	} while ((resp != 'y') && (resp != 'n'));
	if (resp == 'y')
	{
		info->bIsStudent = 1;
	}
	else
	{
		info->bIsStudent = 0;
	}
	printf("Name : ");
	scanf("%s", &info->pcName[0]);
	number++;
	printf("Enter Month: ");
	scanf("%hi", &info->usMonthValidFor);
	printf("Enter Day: ");
	scanf("%hi", &info->usDayBought);
}



float getMonthlyPassPrice(buy_pass_info *info)
{
	PASS_TYPE type = MONTHLY;
	float price = getPriceOfPass(&type, info);
	if (price != -1)
	{
		printf("Monthly Pass Price %f\n", price);
	}
	else
	{
		printf("Could not get Pass Price\n");
	}
	return price;
}
float getPerRidePassPrice(buy_pass_info *info)
{
	PASS_TYPE type = PAY_PER_RIDE;
	float price = getPriceOfPass(&type, info);

	printf("Per Ride Pass Price %f\n", price);
	return price;
}

float handleMoney(PASS_TYPE pass, buy_pass_info *info)
{
	float moneyIn;
	if (pass == MONTHLY)
	{
		if (getMonthlyPassPrice(info) >= 0)
		{
			printf("Please Enter Money: ");
			scanf("%f", &moneyIn);
		}
		
	}
	else
	{
		if (getPerRidePassPrice(info) >= 0)
		{
			printf("Please Enter Money: ");
			scanf("%f", &moneyIn);
		}
	}

	return moneyIn;
}

void output(unsigned short rc, unsigned long id, float moneyOut)
{
	if (rc)
	{
		printf(" Thank you for you purchase ID %lu, Money Back %f\n", id, moneyOut);
	}
	else
	{
		printf(" There has been an issue buying.");
	}
}

void buyMonthly()
{
	unsigned long id;
	float moneyOut;
	PASS_TYPE type = MONTHLY;
	buy_pass_info info;
	info.pcName = &names[number][0];
	
	printf("Buy Monthly Pass Fill out Info\n");
	getInputData(&info);
	float moneyIn = handleMoney(MONTHLY, &info);
	unsigned short rc = buyPass(&type, &id, moneyIn, &moneyOut, &info );

	output(rc, id, moneyOut);
}

void buyPerRide()
{
	unsigned long id;
	float moneyOut;
	PASS_TYPE type = PAY_PER_RIDE;
	buy_pass_info info;
	info.pcName = &names[number][0];

	getInputData(&info);
	float moneyIn = handleMoney(type, &info);
	unsigned short rc = buyPass(&type, &id, moneyIn, &moneyOut, &info);
	
	output(rc, id, moneyOut);
}

void renewPassMonthly()
{
	unsigned long id;
	float price, inMoney, moneyOut;
	unsigned short currentMonth;
	unsigned short currentDay;
	PASS_TYPE type = MONTHLY;
	printf("Renew Monthly Pass\n Please enter ID : ");
	scanf("%li", &id);
	printf("Current Month : ");
	scanf("%hi", &currentMonth);
	printf("Current Day : ");
	scanf("%hi", &currentDay);
	if (isValidPass(&id, &type))
	{
		if (getRenewPrice(&id, &type, &price, currentDay, currentMonth))
		{
			printf("Monthly Pass renew amount is %f\n", price);
			printf(" Please enter money : ");
			scanf("%f", &inMoney);
			if (renewPass(&id, currentDay, currentMonth, inMoney, &moneyOut))
			{
				printf("Pass renewed!\n");
			}
			else
			{
				printf("There was an error renewing pass!\n");
			}

			printf("  Money returned %f\n", moneyOut);
		}
		else
		{
			printf("Error finding info on pass %lu\n", id);
		}
	}
}
void addMoney()
{
	unsigned long id = 0;
	float price = 0.0, inMoney = 0.0, moneyOut = 0.0;
	PASS_TYPE type = PAY_PER_RIDE;
	printf("Renew Monthly Pass\n Please enter ID : ");
	scanf("%li", &id);
	printf(" Please enter money : ");
	scanf("%f", &inMoney);
	if (isValidPass(&id, &type))
	{
		if (addCurrencyToPass(&id, inMoney))
		{
			printf(" Amount %f was added to pass %lu\n", inMoney, id);
		}
		else
		{
			printf(" Error adding money to pass %lu. Refunding %f", id, inMoney);
		}
	}
}

void buy()
{
	printf("--Buy Pass Menu--\n");
	printf(" 1. Buy Monthly Pass\n");
	printf(" 2. Buy Per Ride Pass\n");
	printf(" 3. Renew Pass\n");
	printf(" 4. Add currency to Pass\n");
	unsigned short input = 0;
	printf(" Input: ");
	scanf("%hi", &input);

	switch (input)
	{
	case 1:
		buyMonthly();
		break;
	case 2: 
		buyPerRide();
		break;
	case 3:
		renewPassMonthly();
		break;
	case 4:
		addMoney();
		break;
	default:
		break;
	}

}

void checkBalance()
{
	unsigned long id = 0;
	float balance = 0.0;
	PASS_TYPE type = PAY_PER_RIDE;
	printf("Check Balance\n Enter ID :");
	scanf("%li", &id);
	if (isValidPass(&id,&type) && checkPassBalance(&id, &balance))
	{
		printf(" Balance for %li is %f\n", id, balance);
	}
	else
	{
		printf(" Pass balance cannot be found for pass %li\n", id);
	}
}

void checkIfPassValid()
{
	unsigned long id = 0;
	unsigned short valid = 0;
	unsigned short month = 0;
	printf("Check Monthly Pass\n Enter ID :");
	scanf("%lu", &id);
	if (checkMonthlyValid(&id, &valid, &month))
	{
		printf(" Pass %li is %s. It %s %i\n", id, valid ? "valid" : "expired",
			valid ? "expires" : "expired", month);
	}
	else
	{
		printf(" Pass cannot be found %li\n", id);
	}
}

void usePass()
{
	unsigned long id = 0;
	unsigned short day = 0; 
	unsigned short month = 0;
	unsigned short isWeekend = 0;
	PASS_TYPE type = MONTHLY;
	printf("Use pass menu: \n Enter ID: ");
	scanf("%lu`", &id);
	if (getPassType(&id, &type))
	{
		if (type == MONTHLY)
		{
			//Pass exists and it's a MONTHLY pass
			printf(" Day of ride :");
			scanf("%hi", &day);
			printf(" Month of ride :");
			scanf("%hi", &month);
			//Try to use pass
			if (useMonthly(&id, day, month))
			{
				printf("Using pass %li success\n", id);
			}
			else
			{
				printf("Pass %li failed\n", id);
			}
		}
		else
		{
			if (type == PAY_PER_RIDE)
			{
				//Valid pass
				printf(" Is today a weekend (1,0) :");
				scanf("%hi", &isWeekend);
				float price = getPerRidePrice(&id, isWeekend);
				if (price != -1)
				{
					printf(" A ride will cost %f\n Continue (1,0): ", price);
					short cont = 0;
					scanf("%hi", &cont);
					if (cont && usePerRide(&id, isWeekend))
					{
						printf("Using per ride pass %li successful\n", id);
					}
				}
				else
				{
					printf("Using pass %li failed. Check balance\n", id);
				}
			}
			else
			{
				printf("Pass %li is not a monthly pass\n", id);
			}
		}
		
	}
	else
	{
		printf("Pass %li does not exist\n", id);
	}
}

void use()
{
	unsigned short val = 0;
	unsigned short n = 0;
	printf("Use Menu\n 1. Use for ride\n 2. Check balance(Per Ride)\n 3. Check if valid (Monthly)\n Enter: ");
	scanf("%hi", &val);
	if (val == 1)
	{
		usePass();
	}
	if (val == 2)
	{
		checkBalance();
	}
	if (val == 3)
	{
		checkIfPassValid();
	}
}

void exitProg()
{
	unInit();	
}

void debug()
{
	pass *val = 0x00;
	printf("Printing Monthly Queue\n");
	val = debugGetMonthly();
	while (val)
	{
		printf("Entry ID %lu\n", val->ulID);
		printf(" Name %s\n",&val->pcName[0]);
		printf(" Elderly %i\n", val->bIsElderly);
		printf(" Student %i\n", val->bIsStudent);
		monthly_pass *p = (monthly_pass *)val->pPassData;
		printf(" Monthly Pass Data\n");
		printf("   Month : %i\n", p->usMonthValidFor);
		printf("   Day   : %i\n", p->usDayBought);
		val = debugGetMonthly();
	}
	printf("Printing Per Ride Queue\n");
	val = debugGetPerRide();
	while (val)
	{
		printf("Entry ID %lu\n", val->ulID);
		printf(" Name %s\n", &val->pcName[0]);
		printf(" Elderly %i\n", val->bIsElderly);
		printf(" Student %i\n", val->bIsStudent);
		pay_per_ride_pass *p = (pay_per_ride_pass *)val->pPassData;
		printf(" Per Ride Pass Data\n");
		printf("   Value : %li\n", p->ulCurrentValue);
		val = debugGetPerRide();
	}
}

int main()
{
	init();
	unsigned short state = 0;
	unsigned short usInput = 0;
	while (state != 255) {
		switch (state)
		{
		case 254:
			scanf("%hi", &usInput);
			printf("\n");
			state = usInput;
			break;
		case 0:
			printf("*** Main Menu: *** \n");
			printf("  1. Buy Pass\n");
			printf("  2. Use Pass\n");
			printf("  3. Print DB\n");
                        printf("  4. Exit\n");
			printf("Enter: ");
			state = 254;
			break;
		case 1:
			buy();
			state = 0;
			break;
		case 2:
			use();
			state = 0;
			break;
		case 3:
			debug();
			state = 0;
			break;
                case 4:
                        exitProg();
                        state = 255;
                        break;
		default:
			state = 0;
			break;
		};
	}
    return 0;
}

