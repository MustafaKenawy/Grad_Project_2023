/*
 * DIO_prg.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Options
 */


#include "DIO_int.h"


/*
 * Function Definitions
 */
/* Pin Related Function Definition*/
void DIO_VidSetPinDirection (u8 u8PortIdCopy, u8 u8PinIdCopy, u8 u8PinDirCopy)
{
    /* Make sure that the Port ID and Pin ID are in the valid range */
    if ((u8PortIdCopy <= PORTD) && (u8PinIdCopy <= PIN7))
    {
        if ( u8PinDirCopy == OUTPUT )
        {
            /* Check on the Required PORT Number */
            switch (u8PortIdCopy)
            {
            case PORTA:
                SET_Bit(DDRA_Register,u8PinIdCopy);
                break;
            case PORTB:
                SET_Bit(DDRB_Register,u8PinIdCopy);
                break;
            case PORTC:
                SET_Bit(DDRC_Register,u8PinIdCopy);
                break;
            case PORTD:
                SET_Bit(DDRD_Register,u8PinIdCopy);
                break;
            }
        }
        else if ( u8PinDirCopy == INPUT )
        {
            /* Check on the Required PORT Number */
            switch (u8PortIdCopy)
            {
            case PORTA:
                CLR_Bit(DDRA_Register,u8PinIdCopy);
                break;
            case PORTB:
                CLR_Bit(DDRB_Register,u8PinIdCopy);
                break;
            case PORTC:
                CLR_Bit(DDRC_Register,u8PinIdCopy);
                break;
            case PORTD:
                CLR_Bit(DDRD_Register,u8PinIdCopy);
                break;
            }
        }

        else
        {
            /* Do nothing, Wrong Direction Required */
        }
    }

    else
    {
        /* Do nothing, Error in the Pin ID or PORT ID */
    }
}

void DIO_VidSetPinValue(u8 u8PortIdCopy, u8 u8PinIdCopy, u8 u8PinValCopy)
{
    /* Make sure that the Port ID and Pin ID are in the valid range */
    if ((u8PortIdCopy <= PORTD) && (u8PinIdCopy <= PIN7))
    {
        if (u8PinValCopy == HIGH)
        {
            /* Check on the Required PORT Number */
            switch (u8PortIdCopy)
            {
            case PORTA:
                SET_Bit(PORTA_Register,u8PinIdCopy);
                break;
            case PORTB:
                SET_Bit(PORTB_Register,u8PinIdCopy);
                break;
            case PORTC:
                SET_Bit(PORTC_Register,u8PinIdCopy);
                break;
            case PORTD:
                SET_Bit(PORTD_Register,u8PinIdCopy);
                break;
            }
        }
        else if (u8PinValCopy == LOW)
        {
            /* Check on the Required PORT Number */
            switch (u8PortIdCopy)
            {
            case PORTA:
                CLR_Bit(PORTA_Register,u8PinIdCopy);
                break;
            case PORTB:
                CLR_Bit(PORTB_Register,u8PinIdCopy);
                break;
            case PORTC:
                CLR_Bit(PORTC_Register,u8PinIdCopy);
                break;
            case PORTD:
                CLR_Bit(PORTD_Register,u8PinIdCopy);
                break;
            }
        }
        else
        {
            /* Do nothing, Wrong value to set */
        }
    }
    else
    {
        /* Do nothing, Error in the Pin ID or PORT ID */
    }
}
u8 u8ResultLocal;
u8 DIO_u8GetPinValue(u8 u8PortIdCopy, u8 u8PinIdCopy)
{
    /* Define Local Variable to get the BIT Value */
    //u8 u8ResultLocal;

    /* Make sure that the Port ID and Pin ID are in the valid range */
    if ((u8PortIdCopy <= PORTD) && (u8PinIdCopy <= PIN7))
    {
        /* Check on the Required PORT Number */
        switch (u8PortIdCopy)
        {
        case PORTA:
            u8ResultLocal= GET_Bit(PINA_Register,u8PinIdCopy);
            break;
        case PORTB:
            u8ResultLocal= GET_Bit(PINB_Register,u8PinIdCopy);
            break;
        case PORTC:
            u8ResultLocal= GET_Bit(PINC_Register,u8PinIdCopy);
            break;
        case PORTD:
            u8ResultLocal= GET_Bit(PIND_Register,u8PinIdCopy);
            break;
        }
    }
    else
    {
        /* return 0xff in case of error in the Pin ID or PORT ID */
        u8ResultLocal = 0xFF; /* 255 */
    }
    return u8ResultLocal;
}

/* Port Related Function Definition*/
void DIO_VidSetPortDirection (u8 u8PortId, u8 u8PortDir)
{
    /* Check on the Required PORT Number */
    switch (u8PortId)
    {
    case     PORTA:
        DDRA_Register = u8PortDir;
        break;
    case     PORTB:
        DDRB_Register = u8PortDir;
        break;
    case     PORTC:
        DDRC_Register = u8PortDir;
        break;
    case     PORTD:
        DDRD_Register = u8PortDir;
        break;
    default: /* Wrong Port ID */
        break;
    }
}

void DIO_VidSetPortValue (u8 u8PortId, u8 u8PortVal)
{
    /* Check on the Required PORT Number */
    switch (u8PortId)
    {
    case     PORTA:
        PORTA_Register = u8PortVal;
        break;
    case     PORTB:
        PORTB_Register = u8PortVal;
        break;
    case     PORTC:
        PORTC_Register = u8PortVal;
        break;
    case     PORTD:
        PORTD_Register = u8PortVal;
        break;
    default: /* Wrong Port ID */
        break;
    }
}
void DIO_VoidTogglepin(u8 u8portcopy,u8  u8pincopy)
{
    switch( u8portcopy)
    {
    case 0:
        TOG_BIT( PORTA_Register,  u8pincopy);
        break;
    case 1:
        TOG_BIT(PORTB_Register,  u8pincopy);
        break;
    case 2:
        TOG_BIT(PORTC_Register,  u8pincopy);
        break;
    case 3:
        TOG_BIT(PORTD_Register,  u8pincopy);
        break;
    }
}





