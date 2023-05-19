/*****************************************************************/
/*****************************************************************/
/*****************		Author: Mohamed Magdy	******************/
/*****************		Layer:  MCAL			******************/
/*****************		SWC:    TIMERS			******************/
/*****************		Version:1.00 			******************/
/*****************************************************************/
/*****************************************************************/
#include "../../4-LIB/BIT_MATH.h"
#include "../../4-LIB/STD_TYPES.h"
#include "../../1-MCAL/6-Timers/TIMER_config.h"
#include "../../1-MCAL/6-Timers/TIMER_interface.h"
#include "../../1-MCAL/6-Timers/TIMER_private.h"
#include "../../1-MCAL/6-Timers/TIMER_register.h"


static void (*TIMER0_pvCallBackFunc)(void) = NULL;
static void (*ICU_pvCallBackFunc)(void) = NULL;

void TIMER0_u8Init(void)
{
	/*Waveform generation mode selection*/
	TCCR0 &= TIMER_MODE_MASK;
	TCCR0 |= TIMER_COUNTER0_MODE;


#if TIMER_COUNTER0_MODE == NORMAL

#elif TIMER_COUNTER0_MODE == PWM_PHASE_CORRECT

#elif TIMER_COUNTER0_MODE == CTC

	/*Enable output compare match interrupt*/
	SET_BIT(TIMSK,TIMSK_OCIE0);

	/*Compare Output mode Selection*/
	TCCR0 &= COMPARE_OUTPUT_MASK;
	TCCR0 |= OUTPUT_COMPARE_MODE_NON_PWM;

	/*Set Compare match value*/
	OCR0 = 125;

#elif TIMER_COUNTER0_MODE == FAST_PWM
	/*Make duty cycle 25%*/
	OCR0 = (u8)(256*(0.01*TIMER0_DUTY_CYCLE));

	/*Compare Output mode Selection*/
	TCCR0 &= COMPARE_OUTPUT_MASK;
	TCCR0 |= OUTPUT_COMPARE_MODE_FAST_PWM;

#endif

	/*Selecting Prescaler bits*/
	TCCR0 &= CLK_SELECT_MASK;
	TCCR0 |= CLK_SELECTION;
}

void TIMER1_u8Init(void)
{
#if TIMER_COUNTER1_MODE == NORMAL

#elif TIMER_COUNTER1_MODE == FAST_PWM
	/*Setting Compare output mode Non-inverting Fast PWM*/
	SET_BIT(TCCR1A,TCCR1A_COM1A1);
	CLR_BIT(TCCR1A,TCCR1A_COM1A0);

	/*Setting Waveform Generation Mode*/
	CLR_BIT(TCCR1A,TCCR1A_WGM10);
	SET_BIT(TCCR1A,TCCR1A_WGM11);
	SET_BIT(TCCR1B,TCCR1B_WGM12);
	SET_BIT(TCCR1B,TCCR1B_WGM13);

#endif

	/*Setting the prescaler*/
	TCCR1B &= CLK_SELECT_MASK;
	TCCR1B |= CLK_SELECTION_TIMER1;
}

void ICU_voidInit(void)
{
	/*Set trigger source to rising edge initially*/
	SET_BIT(TCCR1B,TCCR1B_ICES1);

	/*Enable input capture interrupt*/
	SET_BIT(TIMSK,TIMSK_TICIE1);
}

u8 ICU_voidSetTriggerEdge(u8 Copy_u8Edge)
{
	u8 Local_u8ErrorStatus = OK;
	switch(Copy_u8Edge)
	{
	case ICU_RISING_EDGE:SET_BIT(TCCR1B,TCCR1B_ICES1);break;
	case ICU_FALLING_EDGE:CLR_BIT(TCCR1B,TCCR1B_ICES1);break;
	default:Local_u8ErrorStatus = NOT_OK;break;
	}
	return Local_u8ErrorStatus;
}

void ICU_voidEnableInterrupt(void)
{
	SET_BIT(TIMSK,TIMSK_TICIE1);
}

void ICU_voidDisableInterrupt(void)
{
	CLR_BIT(TIMSK,TIMSK_TICIE1);
}

u16 ICU_u16ReadInputCapture(void)
{
	return ICR1;
}

u8 ICU_u8SetCallBack(void(*Copy_pvCallBackFunc)(void))
{
	u8 Local_u8ErrorStatus = OK;

	if (Copy_pvCallBackFunc != NULL)
	{
		ICU_pvCallBackFunc = Copy_pvCallBackFunc;
	}
	else
	{
		Local_u8ErrorStatus = NULL_POINTER;
	}

	return Local_u8ErrorStatus;
}

void TIMER1_voidSetTimerValue(u16 Copy_u16Value)
{
	TCNT1 = Copy_u16Value;
}

u16 TIMER1_u16ReadTimerValue(void)
{
	return TCNT1;
}

void TIMER1_voidSetICR(u16 Copy_u16Top)
{
	ICR1 = Copy_u16Top;
}
void TIMER1_voidSetCompMatchA(u16 Copy_u16CompareMatch)
{
	OCR1A = Copy_u16CompareMatch;
}

f32 TIMER0_u16GetFreq(void)
{
	f32 Local_f32Freq = 0;
	u16 Local_u16Prescaler =0;
#if CLK_SELECTION == PRESCALER_8_BIT
	Local_f32Freq = SYSTEM_FREQUENCY/8;
	Local_u16Prescaler=8;
#elif CLK_SELECTION == PRESCALER_64_BIT
	Local_f32Freq = SYSTEM_FREQUENCY/64;
	Local_u16Prescaler=64;
#elif CLK_SELECTION == PRESCALER_256_BIT
	Local_f32Freq = SYSTEM_FREQUENCY/256;
	Local_u16Prescaler=256;
#elif CLK_SELECTION == PRESCALER_1024_BIT
	Local_f32Freq = SYSTEM_FREQUENCY/1024;
	Local_u16Prescaler=1024;
#endif
	return Local_f32Freq*(Local_u16Prescaler/8);
}

u8 TIMER0_u8SetCallBack( void(*Copy_pvCallBackFunc) (void))
{
	u8 Local_u8ErrorState = OK;
	if (Copy_pvCallBackFunc != NULL)
	{
		TIMER0_pvCallBackFunc = Copy_pvCallBackFunc;
	}
	else
	{
		Local_u8ErrorState = NULL_POINTER;
	}

	return Local_u8ErrorState;
}


void TIMER0_voidSetCompareMatchValue(u8 Copy_u8Value)
{
	OCR0 = Copy_u8Value;
}



/*Interrupt Vector of TIMER0 Compare match mode*/
void __vector_10(void) __attribute__((signal));
void __vector_10(void)
{
	if(TIMER0_pvCallBackFunc != NULL)
	{
		TIMER0_pvCallBackFunc();
	}
}

/*Interrupt Vector of TIMER0 Overflow mode*/
void __vector_11(void) __attribute__((signal));
void __vector_11(void)
{
	if(TIMER0_pvCallBackFunc != NULL)
	{
		TIMER0_pvCallBackFunc();
	}
}

/*Interrupt Vector of ICU*/
void __vector_6(void) __attribute__((signal));
void __vector_6(void)
{
	if(ICU_pvCallBackFunc != NULL)
	{
		ICU_pvCallBackFunc();
	}
}
