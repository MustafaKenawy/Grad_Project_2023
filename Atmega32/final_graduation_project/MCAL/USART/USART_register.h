/*
 * USART_register.h
 *
 *  Created on: Sep 4, 2022
 *      Author: abdul
 */

#ifndef USART_REGISTER_H_
#define USART_REGISTER_H_

#include "USART_interface.h"

#define UDR				*((volatile u8*)0x2c)

#define UCSRA			*((volatile u8*)0x2b)
#define UCSRA_RXC		7
#define UCSRA_UDRE		5


#define UCSRB			*((volatile u8*)0x2a)
#define UCSRB_RXEN		4
#define UCSRB_TXEN		3
#define UCSRB_UCSZ2		2



#define UCSRC			*((volatile u8*)0x40)
#define UCSRC_URSEL		7
#define UCSRC_UCSZ1		2
#define UCSRC_UCSZ0		1


#define UBRRH			*((volatile u8*)0x40)

#define UBRRL			*((volatile u8*)0x29)






#endif /* USART_REGISTER_H_ */
