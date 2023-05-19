/*****************************************************************/
/*****************************************************************/
/*****************		Author: Mohamed Magdy	******************/
/*****************		Layer:  MCAL			******************/
/*****************		SWC:    PORT			******************/
/*****************		Version:1.00 			******************/
/*****************************************************************/
/*****************************************************************/
#include "../../4-LIB/STD_TYPES.h"
#include "../../1-MCAL/2-PORT/PORT_config.h"
#include "../../1-MCAL/2-PORT/PORT_interface.h"
#include "../../1-MCAL/2-PORT/PORT_private.h"
#include "../../1-MCAL/2-PORT/PORT_register.h"



void PORT_voidInit(void)
{
	DDRA = PORTA_DIR;
	DDRB = PORTB_DIR;
	DDRC = PORTC_DIR;
	DDRD = PORTD_DIR;
	
	PORTA = PORTA_INIT_VALUE;
	PORTB = PORTB_INIT_VALUE;
	PORTC = PORTC_INIT_VALUE;
	PORTD = PORTD_INIT_VALUE;
}
