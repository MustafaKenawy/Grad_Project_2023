/*
 * I2C_int.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Options
 */

#ifndef MCAL_I2C_I2C_INT_H_
#define MCAL_I2C_I2C_INT_H_

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "I2C_pri.h"


void I2C_mater_Iint(void);
void I2C_start(void);
void I2C_stop(void);
void I2C_write(u8 data);
u8 I2C_read(u8 ack);
u8 I2C_GETSTATUS(void);







#endif /* MCAL_I2C_I2C_INT_H_ */
