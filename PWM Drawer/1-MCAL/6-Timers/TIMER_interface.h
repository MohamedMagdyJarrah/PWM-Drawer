/*****************************************************************/
/*****************************************************************/
/*****************		Author: Mohamed Magdy	******************/
/*****************		Layer:  MCAL			******************/
/*****************		SWC:    TIMERS			******************/
/*****************		Version:1.00 			******************/
/*****************************************************************/
/*****************************************************************/

#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_

#define ICU_RISING_EDGE				1
#define ICU_FALLING_EDGE			0

/*Functions to initialize timers*/
void TIMER0_u8Init(void);
void TIMER0_voidSetCompareMatchValue(u8 Copy_u8Value);
f32 TIMER0_u16GetFreq(void);

void TIMER1_u8Init(void);
void TIMER1_voidSetICR(u16 Copy_u16Top);
void TIMER1_voidSetCompMatchA(u16 Copy_u16CompareMatch);
void TIMER1_voidSetTimerValue(u16 Copy_u16Value);
u16 TIMER1_u16ReadTimerValue(void);


void TIMER2_u8Init(void);

void ICU_voidInit(void);
u8 ICU_voidSetTriggerEdge(u8 Copy_u8Edge);
void ICU_voidEnableInterrupt(void);
void ICU_voidDisableInterrupt(void);
u16 ICU_u16ReadInputCapture(void);
u8 ICU_u8SetCallBack(void(*Copy_pvCallBackFunc)(void));

/*Functions to set timers*/
u8 TIMER0_u8SetCallBack( void(*Copy_pvCallBackFunc) (void));


#endif
