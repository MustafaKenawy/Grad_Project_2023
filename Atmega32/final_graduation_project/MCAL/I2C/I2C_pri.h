/*
 * I2C_pri.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Options
 */

#ifndef MCAL_I2C_I2C_PRI_H_
#define MCAL_I2C_I2C_PRI_H_

#include "I2C_int.h"

#define  TWBR        *((volatile u8*)  0x20)
#define  TWSR        *((volatile u8*)  0x21)
#define  TWAR        *((volatile u8*)  0x22)
#define  TWCR        *((volatile u8*)  0x56)
#define  TWDR        *((volatile u8*)  0x23)

/*I2C Control Register -TWCR*/
#define TWINT     7
#define TWEA      6
#define TWSTA     5
#define TWSTO     4
#define TWWC      3
#define TWEN      2
#define TWIE      0


/*I2C Status Register -TWSR*/
#define TWS7      7
#define TWS6      6
#define TWS5      5
#define TWS4      4
#define TWS3      3
#define TWPS1     1
#define TWPS0     0

/*I2C Slave Adress Register -TWAR*/
#define TWGCE     0







#endif /* MCAL_I2C_I2C_PRI_H_ */
