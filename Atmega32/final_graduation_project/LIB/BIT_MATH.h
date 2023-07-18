/*
 * BIT_MATH.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Options
 */

#ifndef LIB_BIT_MATH_H_
#define LIB_BIT_MATH_H_

#define SET_Bit(VAR,BITNO)			(VAR)|= (1<<(BITNO))
#define CLR_Bit(VAR,BITNO)			(VAR)&= ~(1<<(BITNO))
#define TOG_BIT(VAR,BITNO)			(VAR)^= (1<<(BITNO))
#define GET_Bit(VAR,BITNO)			(((VAR)>>(BITNO)) & 0x01)
#define IS_BIT_CLEAR(VAR,BITNO)		(!(VAR & (1<< BITNO) ))


#endif /* LIB_BIT_MATH_H_ */
