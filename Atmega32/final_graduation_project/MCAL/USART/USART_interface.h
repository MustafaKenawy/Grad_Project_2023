/*

 * USART_interface.h
 *
 *  Created on: Sep 4, 2022
 *      Author: abdul
 */
#ifndef USART_INTERFACE_H_
#define USART_INTERFACE	_H_

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include <util/delay.h>
#include "USART_register.h"

#define BAUD 9600
#define F_CPU 16000000UL
#define BAUD_PRESCALER (((F_CPU / (BAUD * 16UL))) - 1)

//
//#define Baudrate_9600	51
//
//void UART_voidInit(void);
//void UART_voidSendData(u8 Copy_u8Data);
//u8 UART_voidRecieveData(void);
//void  UART_sendString(u8 *str);
void USART_Init(unsigned int baud_rate);
void UART_voidSendData(unsigned char data);
unsigned char UART_voidRecieveData(void);
void UART_FLUSH();
int serialParseInt();

#endif

