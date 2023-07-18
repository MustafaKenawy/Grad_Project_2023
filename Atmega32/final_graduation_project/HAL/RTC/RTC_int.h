/*
 * RTC.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Options
 */

#ifndef HAL_RTC_RTC_INT_H_
#define HAL_RTC_RTC_INT_H_

#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/I2C/I2C_int.h"
#include <avr/delay.h>

extern u8 rtc_sec,rtc_min, rtc_hour,  rtc_day,rtc_month,rtc_year;

void SET_TIME(u8 sec,u8 min,u8 hour);
void SET_DATE(u8 day,u8 month,u8 year);
void GET_TIME(void);
void GET_DATE(void);
void decimal_to_hexa(unsigned char* number);

#endif /* HAL_RTC_RTC_INT_H_ */
