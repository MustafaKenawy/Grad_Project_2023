/*
 * DIO_int.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Options
 */

#ifndef MCAL_DIO_DIO_INT_H_
#define MCAL_DIO_DIO_INT_H_

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "DIO_pri.h"


#define PORTA    0
#define PORTB    1
#define PORTC    2
#define PORTD    3

/* PIN Defines */
#define PIN0    0
#define PIN1    1
#define PIN2    2
#define PIN3    3
#define PIN4    4
#define PIN5    5
#define PIN6    6
#define PIN7    7

/* PIN Directions */
#define INPUT   0
#define OUTPUT  1

/* PIN Value Options */
#define HIGH    1
#define LOW     0

/*
 * Prototypes
 */
/* Pin Related Prototypes */
/* Set pin as Output or Input */
void DIO_VidSetPinDirection (u8 u8PortIdCopy, u8 u8PinIdCopy, u8 u8PinDirCopy);

/* if pin is output - Set high or low voltage*/
void DIO_VidSetPinValue(u8 u8PortIdCopy, u8 u8PinIdCopy, u8 u8PinValCopy);

/* if pin is input - get value */
u8 DIO_u8GetPinValue(u8 u8PortIdCopy, u8 u8PinIdCopy);

/* Port Related Prototypes */
/* Set port direction */
void DIO_VidSetPortDirection (u8 u8PortId, u8 u8PortDir);

/* if port is output - Set high or low on all pins */
void DIO_VidSetPortValue     (u8 u8PortId, u8 u8PortVal);
void DIO_VoidTogglepin(u8  u8portcopy,u8 u8pincopy);


#endif /* MCAL_DIO_DIO_INT_H_ */
