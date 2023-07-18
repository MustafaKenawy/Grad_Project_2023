/*
 * lcd_prg.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Options
 */
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "../../MCAL/DIO/DIO_int.h"
#include "lcd_int.h"
#include <avr/delay.h>

#include "lcd_cfg.h"

/* Function Prototypes */
void LCD_vidInit(void)
{
	/* Set LCD Pin Directions */
	/* Set Data Port as output */
	DIO_VidSetPinDirection(LCD_PORT_OF_DATA_PINS, LCD_D4_PIN, OUTPUT);
	DIO_VidSetPinDirection(LCD_PORT_OF_DATA_PINS, LCD_D5_PIN, OUTPUT);
	DIO_VidSetPinDirection(LCD_PORT_OF_DATA_PINS, LCD_D6_PIN, OUTPUT);
	DIO_VidSetPinDirection(LCD_PORT_OF_DATA_PINS, LCD_D7_PIN, OUTPUT);

	
	/* Set Control pins as output */
	DIO_VidSetPinDirection(LCD_PORT_OF_CONTROL_PIN_RS, LCD_RS_PIN, OUTPUT);
	DIO_VidSetPinDirection(LCD_PORT_OF_CONTROL_PIN_EN, LCD_EN_PIN, OUTPUT);

	/* Delay 30ms to ensure the initialization of the LCD driver */
	_delay_ms(20);


	/* Function Set  */
	LCD_vidSendCommand(LCD_FUNCTION_SET_8BIT);
	_delay_ms(5);
	LCD_vidSendCommand(LCD_FUNCTION_SET_8BIT);
	_delay_us(150);
	LCD_vidSendCommand(LCD_FUNCTION_SET_8BIT);

	/* Clear Display */
	LCD_vidSendCommand(LCD_CLEAR);
	_delay_ms(5);
	
	/* Return home*/
	LCD_vidSendCommand(LCD_HOME);
	_delay_ms(5);
	
	/* Entry Mode Set  */
	LCD_vidSendCommand(LCD_ENTRY_MODE);
	_delay_ms(2);
	
	/* Display ON OFF Control */
	LCD_vidSendCommand(LCD_DISPLAY_ON);
	_delay_ms(1);
	
	/* select 4 bit mode*/
	LCD_vidSendCommand(LCD_FUNCTION_SET_4BIT);
	_delay_ms(1);
	
	/* set cursor in starting of ddram*/
	LCD_vidSendCommand(LCD_SET_CURSOR);
	_delay_ms(1);

}

void LCD_vidSendCommand(u8 u8CmdCopy)
{

	/* Set RS to LOW */
	DIO_VidSetPinValue(LCD_PORT_OF_CONTROL_PIN_RS, LCD_RS_PIN, LOW);

	/* Set E to HIGH  */
	//DIO_VidSetPinValue(LCD_PORT_OF_CONTROL_PIN_EN, LCD_EN_PIN, HIGH);

	/* Load Command on Data bus */
	DIO_VidSetPinValue(LCD_PORT_OF_DATA_PINS, LCD_D4_PIN, (u8CmdCopy >> 4) & 0x01);
	DIO_VidSetPinValue(LCD_PORT_OF_DATA_PINS, LCD_D5_PIN, (u8CmdCopy >> 5) & 0x01);
	DIO_VidSetPinValue(LCD_PORT_OF_DATA_PINS, LCD_D6_PIN, (u8CmdCopy >> 6) & 0x01);
	DIO_VidSetPinValue(LCD_PORT_OF_DATA_PINS, LCD_D7_PIN, (u8CmdCopy >> 7) & 0x01);

	/* Set E to HIGH  */
	DIO_VidSetPinValue(LCD_PORT_OF_CONTROL_PIN_EN, LCD_EN_PIN, HIGH);
	_delay_us(20);
	
	/* Set E to LOW */
	DIO_VidSetPinValue(LCD_PORT_OF_CONTROL_PIN_EN, LCD_EN_PIN, LOW);

	DIO_VidSetPinValue(LCD_PORT_OF_DATA_PINS, LCD_D4_PIN, (u8CmdCopy >> 0) & 0x01);
	DIO_VidSetPinValue(LCD_PORT_OF_DATA_PINS, LCD_D5_PIN, (u8CmdCopy >> 1) & 0x01);
	DIO_VidSetPinValue(LCD_PORT_OF_DATA_PINS, LCD_D6_PIN, (u8CmdCopy >> 2) & 0x01);
	DIO_VidSetPinValue(LCD_PORT_OF_DATA_PINS, LCD_D7_PIN, (u8CmdCopy >> 3) & 0x01);

	/* Set E to HIGH  */
	DIO_VidSetPinValue(LCD_PORT_OF_CONTROL_PIN_EN, LCD_EN_PIN, HIGH);
	_delay_us(20);
	
	/* Set E to LOW */
	DIO_VidSetPinValue(LCD_PORT_OF_CONTROL_PIN_EN, LCD_EN_PIN, LOW);

	/* Delay for 10ms to let the LCD execute command */
	_delay_ms(10);

}

void LCD_vidWriteChar(u8 u8DataCopy)
{
	/* Set RS to LOW */
	DIO_VidSetPinValue(LCD_PORT_OF_CONTROL_PIN_RS, LCD_RS_PIN, HIGH);


	/* Load Command on Data bus */
	DIO_VidSetPinValue(LCD_PORT_OF_DATA_PINS, LCD_D4_PIN, (u8DataCopy >> 4) & 0x01);
	DIO_VidSetPinValue(LCD_PORT_OF_DATA_PINS, LCD_D5_PIN, (u8DataCopy >> 5) & 0x01);
	DIO_VidSetPinValue(LCD_PORT_OF_DATA_PINS, LCD_D6_PIN, (u8DataCopy >> 6) & 0x01);
	DIO_VidSetPinValue(LCD_PORT_OF_DATA_PINS, LCD_D7_PIN, (u8DataCopy >> 7) & 0x01);

	/* Set E to HIGH  */
	DIO_VidSetPinValue(LCD_PORT_OF_CONTROL_PIN_EN, LCD_EN_PIN, HIGH);
	_delay_us(20);
	
	/* Set E to LOW */
	DIO_VidSetPinValue(LCD_PORT_OF_CONTROL_PIN_EN, LCD_EN_PIN, LOW);

	DIO_VidSetPinValue(LCD_PORT_OF_DATA_PINS, LCD_D4_PIN, (u8DataCopy >> 0) & 0x01);
	DIO_VidSetPinValue(LCD_PORT_OF_DATA_PINS, LCD_D5_PIN, (u8DataCopy >> 1) & 0x01);
	DIO_VidSetPinValue(LCD_PORT_OF_DATA_PINS, LCD_D6_PIN, (u8DataCopy >> 2) & 0x01);
	DIO_VidSetPinValue(LCD_PORT_OF_DATA_PINS, LCD_D7_PIN, (u8DataCopy >> 3) & 0x01);

	/* Set E to HIGH  */
	DIO_VidSetPinValue(LCD_PORT_OF_CONTROL_PIN_EN, LCD_EN_PIN, HIGH);
	_delay_us(20);
	
	/* Set E to LOW */
	DIO_VidSetPinValue(LCD_PORT_OF_CONTROL_PIN_EN, LCD_EN_PIN, LOW);

	/* Delay for 10ms to let the LCD execute command */
	_delay_ms(10);
}

void LCD_vidWriteString (const u8* pu8StringCopy)
{
	/* Local loop index */
	u8 u8Index = 0;
	while (pu8StringCopy[u8Index] != '\0')
	{
		/* Write Character on LCD */
		LCD_vidWriteChar(pu8StringCopy[u8Index]);

		/* Increment local loop index */
		u8Index++;

		/* Delay to let the LCD show the character */
		_delay_ms(2);
	}

}

void LCD_VidGotoRawCol(u8 u8RawCopy, u8 u8ColCopy)
{
	u8 Address;
	switch(u8RawCopy)
	{
		case 0:
			Address = u8ColCopy;
			break;
		case 1:
			Address = u8ColCopy+0x40;
			break;
		case 2:
			Address = u8ColCopy+0x14;
			break;
		case 3:
			Address = u8ColCopy+0x54;
			break;
	}
	LCD_vidSendCommand(Address | LCD_SET_CURSOR);
}


void LCD_IntegerToString(u16 copy_u8num)
{
	u32 i, rem, len=0,n;
	u8 str[20]={0};
	n = copy_u8num;
	while(n!=0)
	{
		len++;
		n/=10;
	}
	for(i=0; i<len;i++)
	{
		rem = copy_u8num %10;
		copy_u8num = copy_u8num /10;
		str[len - (i+1)] = rem + '0';
	}
	str[len] = '\0';
	LCD_vidWriteString(str);
}
