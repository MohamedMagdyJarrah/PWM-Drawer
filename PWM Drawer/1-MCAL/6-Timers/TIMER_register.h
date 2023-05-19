/*****************************************************************/
/*****************************************************************/
/*****************		Author: Mohamed Magdy	******************/
/*****************		Layer:  MCAL			******************/
/*****************		SWC:    TIMERS			******************/
/*****************		Version:1.00 			******************/
/*****************************************************************/
/*****************************************************************/

#ifndef TIMER_REGISTER_H_
#define TIMER_REGISTER_H_

/*Timer interrupt Registers*/
#define TIMSK					*((volatile u8*)0x59)			//Timer Interrupt Mask Register
#define TIMSK_TOIE0				0								//Timer overflow interrupt enable
#define TIMSK_OCIE0				1								//Output Compare match 0 interrupt enable
#define TIMSK_TICIE1			5								//Input capture interrupt enable

#define TIFR					*((volatile u8*)0x58)			//Timer Interrupt flags Register

/*Timer 0 Registers*/
#define TCCR0					*((volatile u8*)0x53)			//Timer/Counter 0 Control Register
#define TCCR0_FOC0				7								//Force Output compare bit
#define TCCR0_WGM00				6								//Waveform generation Mode bit 0
#define TCCR0_COM01				5								//Compare match output mode bit 1
#define TCCR0_COM00				4								//Compare match output mode bit 0
#define TCCR0_WGM01				3								//Waveform generation Mode bit 1
#define TCCR0_CS02				2								//Prescaler selection bit 2
#define TCCR0_CS01				1								//Prescaler selection bit 1
#define TCCR0_CS00				0								//Prescaler selection bit 0
		
#define TCNT0					*((volatile u8*)0x52)			//Timer/Counter 0 Register

#define OCR0					*((volatile u8*)0x5C)			//Output Compare Match 0 Register
		
		
/*Timer 1 Registers*/		
#define TCCR1A					*((volatile u8*)0x4F)
#define TCCR1A_WGM10			0
#define TCCR1A_WGM11			1
#define TCCR1A_COM1A0			6
#define TCCR1A_COM1A1			7

#define TCCR1B					*((volatile u8*)0x4E)
#define TCCR1B_ICES1			6								//Input capture edge select
#define TCCR1B_WGM12			3
#define TCCR1B_WGM13			4
#define TCCR1B_CS12				2								//Prescaler selection bit 2
#define TCCR1B_CS11				1								//Prescaler selection bit 1
#define TCCR1B_CS10				0

#define TCNT1					*((volatile u16*)0x4C)

#define ICR1					*((volatile u16*)0x46)

#define OCR1A					*((volatile u16*)0x4A)
		
/*Timer 2 Registers*/		
#define TCCR2					*((volatile u8*)0x45)			//Timer/Counter 2 Control Register

#define TCNT2					*((volatile u8*)0x44)			//Timer/Counter 2 Register

#define OCR2					*((volatile u8*)0x43)			//Output Compare Match 2 Register



#endif
