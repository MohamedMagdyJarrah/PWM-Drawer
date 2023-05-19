/*****************************************************************/
/*****************************************************************/
/*****************		Author: Mohamed Magdy	******************/
/*****************		Layer:  MCAL			******************/
/*****************		SWC:    TIMERS			******************/
/*****************		Version:1.00 			******************/
/*****************************************************************/
/*****************************************************************/

#ifndef TIMER_PRIVATE_H_
#define TIMER_PRIVATE_H_

/*Timer Modes Configrations*/
#define TIMER_MODE_MASK				0xB7			//CLR WGM00:01 bits

#define NORMAL						0xB7
#define PWM_PHASE_CORRECT			0x40
#define CTC							0x08
#define FAST_PWM					0x48

/*Compare Output Mode*/
#define COMPARE_OUTPUT_MASK			0xCF			//CLR Compare output bits
/*Non PWM*/
#define OC_DISCONNECTED				0
#define OC_TOGGLE					0x10
#define OC_CLR						0x20
#define OC_SET						0x30

/*Fast PWM*/
#define OC_DISCONNECTED				0
#define CLR_CM_SET_TOP				0x20
#define SET_CM_CLR_TOP				0x30

/*Clock selection */
#define CLK_SELECT_MASK				0xF8			//CLR Clock selection bits

#define NO_CLK_SOURCE				0
#define NO_PRESCALING				1
#define PRESCALER_8_BIT				2
#define PRESCALER_64_BIT			3
#define PRESCALER_256_BIT			4
#define PRESCALER_1024_BIT			5
#define EXT_CLK_FALLING_EDGE		6
#define EXT_CLK_RISING_EDGE			7


#endif
