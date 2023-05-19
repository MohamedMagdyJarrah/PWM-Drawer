/*****************		Author: Mohamed Magdy	******************/
/*****************		Layer:  HAL				******************/
/*****************		SWC:    SWITCH			******************/
/*****************		Version:1.00 			******************/
/*****************************************************************/
/*****************************************************************/
#include "../../4-LIB/STD_TYPES.h"

#include <util/delay.h>

#include "../../1-MCAL/1-DIO/DIO_interface.h"
#include "../../2-HAL/2-SWITCH/SW_config.h"
#include "../../2-HAL/2-SWITCH/SW_interface.h"
#include "../../2-HAL/2-SWITCH/SW_private.h"



u8 SW_u8GetState(SW_t* Copy_u8Switch,u8* Copy_u8PressingState)
{
	u8 Local_u8ErrorState = 0;
	u8 Local_u8ReadingState;

	DIO_u8GetPinValue(Copy_u8Switch->Port,Copy_u8Switch->Pin,&Local_u8ReadingState);

	if (Copy_u8Switch->PullType == SW_u8PULL_UP)
	{
		if (Local_u8ReadingState == DIO_u8PIN_HIGH)
		{
			*Copy_u8PressingState = SW_u8NOT_PRESSED;
		}
		else if (Local_u8ReadingState == DIO_u8PIN_LOW)
		{
			*Copy_u8PressingState = SW_u8PRESSED;
			if (Copy_u8Switch->SelfLockingType == SW_u8MOMENTARY)
			{
				//_delay_ms(100);
			}
			else if (Copy_u8Switch->SelfLockingType == SW_u8MAINTAINED)
			{
				/*DO NOTHING*/
			}
			else
			{
				Local_u8ErrorState = 1;
			}
		}
	}
	else if (Copy_u8Switch->PullType == SW_u8PULL_DOWN)
	{
		if (Local_u8ReadingState == DIO_u8PIN_HIGH)
		{
			*Copy_u8PressingState = SW_u8PRESSED;
			if (Copy_u8Switch->SelfLockingType == SW_u8MOMENTARY)
			{
				//_delay_ms(100);
			}
			else if (Copy_u8Switch->SelfLockingType == SW_u8MAINTAINED)
			{
				/*DO NOTHING*/
			}
			else
			{
				Local_u8ErrorState = 1;
			}
		}
		else if (Local_u8ReadingState == DIO_u8PIN_LOW)
		{
			*Copy_u8PressingState = SW_u8NOT_PRESSED;
		}
	}
	else
	{
		Local_u8ErrorState = 1;
	}

	return Local_u8ErrorState;
}
