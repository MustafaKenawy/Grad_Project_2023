/*
 * I2C_prog.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Options
 */

#include "I2C_int.h"

void I2C_mater_Iint(void)
{
    /*ENABLE ACK*/
    SET_Bit(TWCR,TWEA);
    /*ENABLE I2C*/
    SET_Bit(TWCR,TWEN);

    /*SPEED OF I2C*/

    /*TWPS-PRESCALER*/
    CLR_Bit(TWSR,TWPS0);
    CLR_Bit(TWSR,TWPS1);
    /*TWBR-VALUE*/
    TWBR=32;
}

void I2C_start(void)
{

    TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
    while ((TWCR &(1<<TWINT))==0);//WAITING FOR FLAG



}
void I2C_stop(void)
{
    TWCR=(1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}


void I2C_write(u8 data)
{

    TWDR=data;
    TWCR=(1<<TWINT)|(1<<TWEN);

    while ((TWCR &(1<<TWINT))==0); //WAITING FOR FLAG


}
u8 I2C_read(u8 ack)
{

    TWCR =(1<<TWINT)|(1<<TWEN)|(ack<<TWEA);
    while ((TWCR &(1<<TWINT))==0); //WAITING FOR FLAG

    return TWDR;
}
u8 I2C_GETSTATUS(void)
{
    u8 status;
    status = TWSR & 0xf8;
    return status;
}

