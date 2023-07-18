/*
 * RTC_prog.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Options
 */

#include "RTC_int.h"

u8 rtc_sec,rtc_min,rtc_hour,rtc_day,rtc_month,rtc_year ;

void SET_TIME(u8 sec,u8 min,u8 hour )
{
    I2C_start();//START CONDITION
    I2C_write(0b11010000);//send address DS3231
    I2C_write(0);//set pointer to 0
    _delay_ms(10);
    I2C_write(sec); //set seconds
    _delay_ms(10);
    I2C_write(min); //set minutes
    _delay_ms(10);
    I2C_write(hour); //set hours
    _delay_ms(10);
    I2C_stop(); // send stop condition
}

void SET_DATE(u8 day,u8 month,u8 year)
{
    I2C_start();//start condition
    I2C_write(0b11010000); //write address ds3231
    I2C_write(04); //set pointer to 4
    _delay_ms(10);
    I2C_write(day); //set days
    _delay_ms(10);
    I2C_write(month); // set months
    _delay_ms(10);
    I2C_write(year); // set years
    _delay_ms(10);;
    I2C_stop(); // send stop condition
}
void GET_TIME(void)
{

    I2C_start(); //start condition
    I2C_write(0b11010000); // write address ds3231
    I2C_write( 0);// set pointer to 0
    I2C_start(); // restart condition
    I2C_write(0xD1); //address ds3231 for read
    rtc_sec= I2C_read(1); // read seconds
    decimal_to_hexa(&rtc_sec); // convert decimal to hex
    rtc_min= I2C_read(1); // read minutes
    decimal_to_hexa(&rtc_min);// convert decimal to hex
    rtc_hour= I2C_read(0); // read hours
    decimal_to_hexa(&rtc_hour); // convert  decimal to hex
    I2C_stop();


}
void GET_DATE(void)
{

    I2C_start(); //start condition
    I2C_write(0b11010000); // write address ds3231
    I2C_write(04); // set pointer to 4
    I2C_start(); // restart condition
    I2C_write(0xD1); // address ds3231 for read
    rtc_day= I2C_read(1); //read days
    decimal_to_hexa(&rtc_day); // convert  decimal to hex
    rtc_month=I2C_read(1); //read month
    decimal_to_hexa(&rtc_month); // convert  decimal to hex
    rtc_year=I2C_read(0);// read years
    decimal_to_hexa(&rtc_year);// convert  decimal to hex
    I2C_stop();// stop condition


}
void decimal_to_hexa(unsigned char* number)
{
    //The RTC store the number as hexadecimal number! so to use the numbers of the RTC we need to convert it to decimal
    //the compiler convert the hexa number to decimal..we want it as hexa.
    unsigned char arr[5];
    int i=0,j=0,count=0;
    int temp1,temp2,temp3=*number;
    while((int)temp3!=0)
    {
        temp1=temp3%16;
        temp3=(int)(temp3/16);
        arr[count++]=temp1;
    }
    count--;
    for(i=0,j=count; i<=j; i++,j--) //convert the numbers to the right order.
    {
        temp2=arr[i];
        arr[i]=arr[j];
        arr[j]=temp2;
    }
    if((*number)>=10 && (*number)<=99)
    {
        *number=(arr[0]*10)+arr[1]*1;
    }
    else if((*number)>=100 && (*number)<=999)
    {
        *number=(arr[0]*100)+(arr[1]*10)+arr[0];
    }
}
