/*
 * lcd_int.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Options
 */


#include "../../LIB/STD_TYPES.h"

#ifndef MCAL_LCD_INT_H_
#define MCAL_LCD_INT_H_
#define LCD_CLEAR                0x01          /* replace all characters with ASCII 'space'     */
#define LCD_HOME                 0x02          /* return cursor to first position on first line */
#define LCD_ENTRY_MODE           0x06          /* shift cursor from left to right on read/write */
#define LCD_DISPLAY_OFF          0x08          /* turn display off                              */
#define LCD_DISPLAY_ON           0x0C          /* display on, cursor off, don't blink character */
#define LCD_FUNCTION_RESET       0x30          /* reset the LCD                                 */
#define LCD_FUNCTION_SET_8BIT    0x38          /* 8-bit data, 2-line display, 5 x 7 font        */
#define LCD_FUNCTION_SET_4BIT    0x28          /* 8-bit data, 2-line display, 5 x 7 font        */
#define LCD_SET_CURSOR           0x80          /* set cursor position                           */
#define _LCD_DISPLAY_ON_CURSOR_OFF_BLINK_ON	   0x0D


/*
 * Rows
 */
#define LCD_ROW0                 0x00
#define LCD_ROW1                 0x01
#define LCD_ROW2                 0x02
#define LCD_ROW3                 0x03

/*
 * Columns
 */
#define LCD_COL0                 0x00
#define LCD_COL1                 0x01
#define LCD_COL2                 0x02
#define LCD_COL3                 0x03
#define LCD_COL4                 0x04
#define LCD_COL5                 0x05
#define LCD_COL6                 0x06
#define LCD_COL7                 0x07
#define LCD_COL8                 0x08
#define LCD_COL9                 0x09
#define LCD_COL10                0x0A
#define LCD_COL11                0x0B
#define LCD_COL12                0x0C
#define LCD_COL13                0x0D
#define LCD_COL14                0x0E
#define LCD_COL15                0x0F
#define LCD_COL16                0x10
#define LCD_COL17                0x11
#define LCD_COL18                0x12
#define LCD_COL19                0x13

/*
 * Functions Prototype
 */
void LCD_vidInit(void);

void LCD_vidSendCommand(u8 u8CmdCopy);

void LCD_vidWriteChar (u8 u8DataCopy);

void LCD_vidWriteString (const u8* pu8StringCopy);

void LCD_VidGotoRawCol (u8 u8RawCopy, u8 u8ColCopy);
void LCD_IntegerToString(u16 copy_u8num);


#endif /* MCAL_LCD_INT_H_ */
