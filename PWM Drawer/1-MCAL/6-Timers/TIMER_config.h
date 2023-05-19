/*****************************************************************/
/*****************************************************************/
/*****************		Author: Mohamed Magdy	******************/
/*****************		Layer:  MCAL			******************/
/*****************		SWC:    TIMERS			******************/
/*****************		Version:1.00 			******************/
/*****************************************************************/
/*****************************************************************/

#ifndef TIMER_CONFIG_H_
#define TIMER_CONFIG_H_

/*Setting System Frequency*/
#define SYSTEM_FREQUENCY					8000000UL

/*Choosing Timer/Counter mode*/
/*Options:
 * 1-NORMAL
 * 2-PWM_PHASE_CORRECT
 * 3-CTC
 * 4-FAST_PWM
 * */
#define TIMER_COUNTER0_MODE					FAST_PWM			//Timer 0 Mode
#define TIMER_COUNTER1_MODE					NORMAL				//Timer 1 Mode
#define TIMER_COUNTER2_MODE					NORMAL				//Timer 2 Mode


/*Choosing Duty Cycle in Case of choosing Fast Pwm*/
#define TIMER0_DUTY_CYCLE					80			// From 13 to 99


/*Choosing Output Compare mode*/
/*Options:(Non PWM)                Options:(Fast PWM)                  Options:(Phase Correct PWM)
 * 1-OC_DISCONNECTED                1-OC_DISCONNECTED                  1-OC_DISCONNECTED
 * 2-OC_TOGGLE                      2-CLR_CM_SET_TOP                   2-OC_TOGGLE
 * 3-OC_CLR                         3-SET_CM_CLR_TOP                   3-OC_CLR
 * 4-OC_SET                         		                           4-OC_SET
 * */
#define OUTPUT_COMPARE_MODE_NON_PWM						OC_DISCONNECTED
#define OUTPUT_COMPARE_MODE_FAST_PWM					CLR_CM_SET_TOP
#define OUTPUT_COMPARE_MODE_PHASE_CORRECT_PWM			OC_DISCONNECTED

/*Clock bits selection*/
/*Options:
 * 1-NO_CLK_SOURCE
 * 2-NO_PRESCALING
 * 3-PRESCALER_8_BIT
 * 4-PRESCALER_64_BIT
 * 5-PRESCALER_256_BIT
 * 6-PRESCALER_1024_BIT
 * 7-EXT_CLK_FALLING_EDGE
 * 8-EXT_CLK_RISING_EDGE
 * */
#define CLK_SELECTION						PRESCALER_64_BIT
#define CLK_SELECTION_TIMER1				PRESCALER_8_BIT

#endif
