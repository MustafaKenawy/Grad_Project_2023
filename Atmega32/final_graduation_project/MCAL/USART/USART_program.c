//
//
//#include "USART_interface.h"
//
//void UART_voidInit(void)
//{
	///* choose baudrate to be equal to 9600 Mbps */
	//UBRRL = Baudrate_9600;
//
	///* enable  URSEL to write on the USCRC register and set 8-bit data */
	//UCSRC = 0b10000110;
//
	///* enable the Rx and Tx */
	//SET_Bit(UCSRB, UCSRB_RXEN);
	//SET_Bit(UCSRB, UCSRB_TXEN);
//
//}
//void UART_voidSendData(u8 Copy_u8Data)
//{
	///* waiting for UDR to be ready to be written */
	//while(IS_BIT_CLEAR(UCSRA, UCSRA_UDRE));
//
	///* write the data on the UDR */
	//UDR = Copy_u8Data;
//}
//
//u8 UART_voidRecieveData(void)
//{
	//u8 Local_u8ReurnedData = 0;
//
	///* waiting for UDR to be ready to be read */
	//while(IS_BIT_CLEAR(UCSRA, UCSRA_RXC));
//
	///* read the data from the UDR */
	//Local_u8ReurnedData = UDR;
//
	//return Local_u8ReurnedData;
//}
///* functon to write string  */
//void UART_sendString(u8 *str)
//{
	//u8 index = 0;
//
	//while(str[index] != '\0')
	//{
		//UART_voidSendData(str[index]);
		//index++;
		//_delay_ms(2);
	//}
//}
//
//
//
//
//
//
//
//


//#include "USART_interface.h"
//
//void UART_voidInit(void)
//{
	///* choose baudrate to be equal to 9600 Mbps */
	//UBRRL = Baudrate_9600;
//
	///* enable  URSEL to write on the USCRC register and set 8-bit data */
	//UCSRC = 0b10000110;
//
	///* enable the Rx and Tx */
	//SET_Bit(UCSRB, UCSRB_RXEN);
	//SET_Bit(UCSRB, UCSRB_TXEN);
//
//}
//void UART_voidSendData(u8 Copy_u8Data)
//{
	///* waiting for UDR to be ready to be written */
	//while(IS_BIT_CLEAR(UCSRA, UCSRA_UDRE));
//
	///* write the data on the UDR */
	//UDR = Copy_u8Data;
//}
//
//u8 UART_voidRecieveData(void)
//{
	//u8 Local_u8ReurnedData = 0;
//
	///* waiting for UDR to be ready to be read */
	//while(IS_BIT_CLEAR(UCSRA, UCSRA_RXC));
//
	///* read the data from the UDR */
	//Local_u8ReurnedData = UDR;
//
	//return Local_u8ReurnedData;
//}
///* functon to write string  */
//void UART_sendString(u8 *str)
//{
	//u8 index = 0;
//
	//while(str[index] != '\0')
	//{
		//UART_voidSendData(str[index]);
		//index++;
		//_delay_ms(2);
	//}
//}

#include "USART_interface.h"



void USART_Init(unsigned int baud_rate) {
	// Set baud rate
	UBRRH = (unsigned char)(baud_rate>>8);
	UBRRL = (unsigned char)baud_rate;
	
	// Enable receiver and transmitter
	UCSRB = (1<<UCSRB_RXEN)|(1<<UCSRB_TXEN);
	
	// Set frame format: 8 data bits, 1 stop bit
	UCSRC = (1<<UCSRC_URSEL)|(1<<UCSRC_UCSZ0)|(1<<UCSRC_UCSZ1);
}

void UART_voidSendData(unsigned char data) {
	// Wait for empty transmit buffer
	while (!(UCSRA & (1<<UCSRA_UDRE)));
	
	// Put data into buffer, send data
	UDR = data;
}

unsigned char UART_voidRecieveData(void) 
{
	UART_FLUSH();
	/*UCSRB &= ~(1<<UCSRB_RXEN);
	UCSRB |= (1<<UCSRB_RXEN);*/
	// Wait for data to be received
	while (!(UCSRA & (1<<UCSRA_RXC)));
	
	// Get and return received data from buffer
	return UDR;
}
void UART_FLUSH()
{

	while(UCSRA & (1 << UCSRA_RXC))
	{
		volatile uint8_t dummy = UDR; // Read the data register and discard the value
	}

}

int serialParseInt()
{
	char buffer[16];
	uint8_t index = 0;
	char receivedChar;
	UART_FLUSH();
	
	while (1)
	{
		while (!(UCSRA & (1 << UCSRA_RXC))); // Wait for data reception
		

		receivedChar = UDR; // Read the received character

		if (receivedChar == '\r' || receivedChar == '\n')
		break; // Stop reading if newline or carriage return is received

		buffer[index++] = receivedChar;

		if (index >= sizeof(buffer) - 1)
		break; // Stop reading if the buffer is full
	}

	buffer[index] = '\0'; // Null-terminate the string

	return atoi(buffer); // Convert the string to an integer using atoi() function
}




