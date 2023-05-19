/*Libraries for Standard Types*/
#include "4-LIB/STD_TYPES.h"
/*Libraries used from MCAL Layer*/
#include "1-MCAL/2-PORT/PORT_interface.h"
#include "1-MCAL/6-Timers/TIMER_interface.h"
#include "1-MCAL/3-EXTI/EXTI_interface.h"
#include "1-MCAL/4-GIE/GIE_interface.h"
/*Libraries used from HAL Layer*/
#include "2-HAL/4-CLCD/CLCD_interface.h"

typedef enum PWM{INTERNAL,EXTERNAL} PWM_SOURCE;

/*Functions Prototypes*/
void ICU(void);
void APP_init(void);
void Display_Screen(void);

/*Variable used in the program*/
PWM_SOURCE WaveformSource = 0;
static u16 PeriodTicks =0;
static u16 OnTicks =0;
static f32 Frequency =0;
static f32 DutyCycle =0.0;
static f64 TickTime = 0;
static u8 ColumnCounter=0;
static u8 Flag=0;

/*Waveform Symbols*/
u8 FirstHalfDuty25[]={0b00011100,0b00010100,0b00010100,0b00010100,0b00010100,0b00010100,0b00010100,0b00010111};
u8 FirstHalfDuty50[]={0b00011111,0b00010001,0b00010001,0b00010001,0b00010001,0b00010001,0b00010001,0b00010001};
u8 FirstHalfDuty75[]={0b00011111,0b00010000,0b00010000,0b00010000,0b00010000,0b00010000,0b00010000,0b00010000};
u8 SecondHalfDuty75[]={0b00011100,0b00000100,0b00000100,0b00000100,0b00000100,0b00000100,0b00000100,0b00000111};
u8 LowLevel[]={0,0,0,0,0,0,0,0xFF};
u8 HighLevel[]={0xFF,0,0,0,0,0,0,0};

int main(void)
{
	/*Choose the Source of the PWM Signal*/
	WaveformSource = INTERNAL;					/*Change it to EXTERNAL when we recieve the signal from another MC*/

	/*Initialization of the application*/
	APP_init();

	while(1)
	{
		/*Waiting Until period and on ticks calculated*/
		while((PeriodTicks == 0) && (OnTicks==0));

		/*Calculating Duty Cycle and the frequency*/
		DutyCycle = 100.0*((f32)OnTicks/(f32)PeriodTicks);
		Frequency = 1/((PeriodTicks+1)*(TickTime));

		/*Display data and the waveform*/
		Display_Screen();
	}
}



void APP_init(void)
{
	/*Initialize Port of LCD (Output pins) and INT0 (Input pin) and OC0 (Output pin) "That will generate internal PWM" */
	PORT_voidInit();

	/*Initialize LCD*/
	CLCD_voidInit();

	/*Initialize External Interrupt*/
	EXTI_u8INT0SetCallBack(&ICU);
	EXTI_voidINT0Init();

	/*Initialize Timer for PWM (Timer 0 generate PWM Signal and Timer 1 read the PWM Signal)*/
	if(WaveformSource == INTERNAL)
	{
		TIMER0_u8Init();
	}
	TIMER1_u8Init();

	/*Enable General Interrupt*/
	GIE_voidEnable();

	/*Calculate TickTime Generated by the Recieved Timer*/
	TickTime = 1/TIMER0_u16GetFreq();
}

void Display_Screen(void)
{
	/*Showing them on the top of the lcd*/
	CLCD_voidWriteNumber(Frequency,0,0,READ_FROM_LEFT);
	CLCD_voidSendString("Hz    ");
	CLCD_u8GoToXY(0,15);
	CLCD_voidSendData('%');
	CLCD_voidWriteNumber((u16)DutyCycle,0,14,READ_FROM_RIGHT);

	/*Showing the Waveform*/
	if((DutyCycle>12 && DutyCycle<=40) && (Flag==0))
	{
		CLCD_u8GoToXY(1,0);
		for(ColumnCounter=0; ColumnCounter <8 ; ColumnCounter++)
		{
			CLCD_voidWriteSpecialCharacter(FirstHalfDuty25,0,1,(ColumnCounter*2));
			CLCD_voidWriteSpecialCharacter(LowLevel,1,1,(ColumnCounter*2)+1);
		}
		Flag=1;
	}
	else if((DutyCycle>40 && DutyCycle<=63) && (Flag==0))
	{
		CLCD_u8GoToXY(1,0);
		for(ColumnCounter=0; ColumnCounter <8 ; ColumnCounter++)
		{
			CLCD_voidWriteSpecialCharacter(FirstHalfDuty50,2,1,(ColumnCounter*2));
			CLCD_voidWriteSpecialCharacter(LowLevel,1,1,(ColumnCounter*2)+1);
		}
		Flag=1;
	}
	else if((DutyCycle>63 && DutyCycle<=85) && (Flag==0))
	{
		CLCD_u8GoToXY(1,0);
		for(ColumnCounter=0; ColumnCounter <8 ; ColumnCounter++)
		{
			CLCD_voidWriteSpecialCharacter(FirstHalfDuty75,3,1,(ColumnCounter*2));
			CLCD_voidWriteSpecialCharacter(SecondHalfDuty75,4,1,(ColumnCounter*2)+1);
		}
		Flag=1;
	}
	else if((DutyCycle>86 && DutyCycle<100) && (Flag==0))
	{
		CLCD_u8GoToXY(1,0);
		for(ColumnCounter=0; ColumnCounter <16 ; ColumnCounter++)
		{
			CLCD_voidWriteSpecialCharacter(HighLevel,5,1,ColumnCounter);
		}
		Flag=1;
	}
}

void ICU(void)
{
	static u8 Local_u8Counter =0;
	Local_u8Counter++;

	if(Local_u8Counter == 1)
	{
		/*First rising edge*/
		TIMER1_voidSetTimerValue(0);

	}
	else if (Local_u8Counter == 2)
	{
		/*Calculating Period Ticks*/
		PeriodTicks = TIMER1_u16ReadTimerValue();

		/*Change trigger edge of interrupt to falling edge*/
		EXTI_u8INTSetSenseControl(INT0,FALLING_EDGE);
	}
	else if(Local_u8Counter == 3)
	{
		/*Calculating On ticks by reading On Ticks + Period Ticks then substracting period ticks from it*/
		OnTicks = TIMER1_u16ReadTimerValue();
		OnTicks -= PeriodTicks;

		/*Disable INT0 Interrput*/
		EXTI_u8INTDisable(INT0);
	}
}
