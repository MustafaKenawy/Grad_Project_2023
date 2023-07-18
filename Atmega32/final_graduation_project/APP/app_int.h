/*
 * app_int.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Options
 */

#ifndef PROJECT_APP_APP_INT_H_
#define PROJECT_APP_APP_INT_H_


#include "../LIB/BIT_MATH.h"
#include "../LIB/STD_TYPES.h"
#include "../MCAL/I2C/I2C_int.h"
#include "../HAL/RTC/RTC_int.h"
#include "../HAL/LCD/lcd_int.h"
#include "../MCAL/USART/USART_interface.h"
#include "../MCAL/DIO/DIO_int.h"
#include "app_pri.h"
#include <util/delay.h>


void open_gate(u16 step);
void close_gate(u16 step);
void down(u16 step);
void up(u16 step);
void rotate_forward(u16 step);
void rotate_reverse(u16 step);
void put(u16 step);
void bring(u16 step);
void stop();
void parking(u8 floor, u8 place);
void retrieving(u8 floor, u8 place);
u32 ctoi(u8 c);
void to_origin(void);



#endif /* PROJECT_APP_APP_INT_H_ */
