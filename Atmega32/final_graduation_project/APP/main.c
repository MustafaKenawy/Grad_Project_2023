///*
 //* main.c
 //*
 //*  Created on: ??þ/??þ/????
 //*      Author: Options
 //*/
//
#include "app_int.h"

/*************************?????1*******************************/
#define GATE_OUT_SENSOR_PIN PIN3
#define GATE_IN_SENSOR_PIN  PIN2

#define GATE_OUT_SENSOR_PORT PORTD
#define GATE_IN_SENSOR_PORT  PORTD

#define GATE_SENSORS_ACTIVE_VALUE HIGH

u8 GateSensorsBuffer = 0;
/*************************************************************/

u32 floor_steps[2] = { FLOOR1_STEPS, FLOOR2_STEPS };
u32 place_steps[4] = { PLACE0_4_STEPS, PLACE1_5_STEPS, PLACE2_6_STEPS, PLACE3_7_STEPS };

u16 high = 0, angle = 0, extension = 0;

u8 temp;
u8 counter = 0;
u8 data;

typedef struct
{
    u8 flag;
     //rtc
} place_t;

place_t places[8];

s8 counter2 = 0, counter1 = 0, flag = 1,flag_clear = 0;

u8 read_up = 0, read_down = 0, read_ok = 0;

u8 garbage = 0, index = 0;

int main(void)
{
    USART_Init(BAUD_PRESCALER);
    DIO_VidSetPinDirection(PORTD,PIN0,INPUT);
    DIO_VidSetPinDirection(PORTD,PIN1,OUTPUT);

    DIO_VidSetPinDirection(PORTB, UP_DOWN_1, OUTPUT);
    DIO_VidSetPinDirection(PORTB, UP_DOWN_2, OUTPUT);
    DIO_VidSetPinDirection(PORTB, UP_DOWN_3, OUTPUT);
    DIO_VidSetPinDirection(PORTB, UP_DOWN_4, OUTPUT);

    DIO_VidSetPinDirection(PORTC, ROTATE_1, OUTPUT);
    DIO_VidSetPinDirection(PORTC, ROTATE_2, OUTPUT);
    DIO_VidSetPinDirection(PORTC, ROTATE_3, OUTPUT);
    DIO_VidSetPinDirection(PORTC, ROTATE_4, OUTPUT);

    DIO_VidSetPinDirection(PORTA, PUT_BRING_1, OUTPUT);
    DIO_VidSetPinDirection(PORTA, PUT_BRING_3, OUTPUT);
    DIO_VidSetPinDirection(PORTA, PUT_BRING_2, OUTPUT);
    DIO_VidSetPinDirection(PORTA, PUT_BRING_4, OUTPUT);
	
	DIO_VidSetPinDirection(PORTA, OPEN_CLOSE1, OUTPUT);
	DIO_VidSetPinDirection(PORTA, OPEN_CLOSE2, OUTPUT);
	DIO_VidSetPinDirection(PORTA, OPEN_CLOSE3, OUTPUT);
	DIO_VidSetPinDirection(PORTA, OPEN_CLOSE4, OUTPUT);
	
	/*************************?????2*******************************/
	DIO_VidSetPinDirection(GATE_IN_SENSOR_PORT, GATE_IN_SENSOR_PIN, INPUT);
	DIO_VidSetPinDirection(GATE_OUT_SENSOR_PORT, GATE_OUT_SENSOR_PIN, INPUT);
	/*************************************************************/
	
	DIO_VidSetPinDirection(PORTD, PIN4, INPUT);		//up
	DIO_VidSetPinDirection(PORTD, PIN5, INPUT);		//down
	DIO_VidSetPinDirection(PORTD, PIN6, INPUT);		//ok
	LCD_vidInit();
	LCD_vidSendCommand(_LCD_DISPLAY_ON_CURSOR_OFF_BLINK_ON);
	
	
    while(1)
    {	
		read_up = DIO_u8GetPinValue(PORTD, PIN4);
		read_down = DIO_u8GetPinValue(PORTD, PIN5);
		read_ok = DIO_u8GetPinValue(PORTD, PIN6);
		
		if(1 == read_up)
		{
			while(1)
			{
				
			//lcd code	
			if(1 == flag)
			{
				if(0 == flag_clear)
				{
					flag_clear = 1;
					LCD_vidSendCommand(LCD_CLEAR);
					LCD_VidGotoRawCol(0,0);
					LCD_vidWriteString(" 1-UP/DOWN");
					LCD_VidGotoRawCol(1,0);
					LCD_vidWriteString("2-PUT/PRING");
					LCD_VidGotoRawCol(2,0);
					LCD_vidWriteString("3-ROTATE FWD/RVS");
					LCD_VidGotoRawCol(3,0);
					LCD_vidWriteString("4-DOOR OPEN/CLOSE");
				}
				
				if(1 == DIO_u8GetPinValue(PORTD, PIN4))
				{
					while(DIO_u8GetPinValue(PORTD, PIN4));
					counter2--;
					if(-1 == counter2)
					{
						counter2 = 3;
					}
				}
				else if(1 == DIO_u8GetPinValue(PORTD, PIN5))
				{
					while(DIO_u8GetPinValue(PORTD, PIN5));
					counter2++;
					if(4 == counter2)
					{
						counter2 = 0;
					}
				}
				LCD_VidGotoRawCol(counter2,0);
				if(1 == DIO_u8GetPinValue(PORTD, PIN6))
				{
					while(DIO_u8GetPinValue(PORTD, PIN6));
					flag++;
				}
				
			}
			else if(2 == flag)
			{
				switch(counter2)
				{
					case 0:
					if(1 == flag_clear)
					{
						flag_clear = 0;
						LCD_vidSendCommand(LCD_CLEAR);
						LCD_VidGotoRawCol(0,0);
						LCD_vidWriteString(" 1-UP");
						LCD_VidGotoRawCol(1,0);
						LCD_vidWriteString("2-down");
						LCD_VidGotoRawCol(2,0);
						LCD_vidWriteString("3-back");
						
					}
					if(1 == DIO_u8GetPinValue(PORTD, PIN4))
					{
						while(DIO_u8GetPinValue(PORTD, PIN4));
						counter1--;
						if(counter1 < 0)
						{
							counter1 = 2;
						}
					}
					else if(1 == DIO_u8GetPinValue(PORTD, PIN5))
					{
						while(DIO_u8GetPinValue(PORTD, PIN5));
						counter1++;
						if(counter1 > 2)
						{
							counter1 = 0;
						}
					}
					LCD_VidGotoRawCol(counter1,0);
					if(1 == DIO_u8GetPinValue(PORTD, PIN6))
					{
						while(DIO_u8GetPinValue(PORTD, PIN6));
						switch(counter1)
						{
							case 0:
								flag_clear = 1;
								LCD_vidSendCommand(LCD_CLEAR);
								LCD_VidGotoRawCol(0,0);
								LCD_vidWriteString(" waiting up func");
								//up function
								up(FLOOR1_STEPS);
								LCD_vidSendCommand(LCD_CLEAR);
								LCD_VidGotoRawCol(0,0);
								LCD_vidWriteString(" up func done");
								_delay_ms(5000);
								break;
							
							case 1 :
								flag_clear = 1;
								LCD_vidSendCommand(LCD_CLEAR);
								LCD_VidGotoRawCol(0,0);
								LCD_vidWriteString(" waiting down func");
								//down function
								down(FLOOR1_STEPS);
								LCD_vidSendCommand(LCD_CLEAR);
								LCD_VidGotoRawCol(0,0);
								LCD_vidWriteString(" down func done");
								_delay_ms(5000);
								break;
							
							case 2:
								flag--;
								counter1 = 0;
								break;
						}
					}
					break;
					
					case 1:
						if(1 == flag_clear)
						{
							flag_clear = 0;
							LCD_vidSendCommand(LCD_CLEAR);
							LCD_VidGotoRawCol(0,0);
							LCD_vidWriteString(" 1-put");
							LCD_VidGotoRawCol(1,0);
							LCD_vidWriteString("2-bring");
							LCD_VidGotoRawCol(2,0);
							LCD_vidWriteString("3-back");
						
						}
						if(1 == DIO_u8GetPinValue(PORTD, PIN4))
						{
							while(DIO_u8GetPinValue(PORTD, PIN4));
							counter1--;
							if(counter1 < 0)
							{
								counter1 = 2;
							}
						}
						else if(1 == DIO_u8GetPinValue(PORTD, PIN5))
						{
							while(DIO_u8GetPinValue(PORTD, PIN5));
							counter1++;
							if(counter1 > 2)
							{
								counter1 = 0;
							}
						}
						LCD_VidGotoRawCol(counter1,0);
						if(1 == DIO_u8GetPinValue(PORTD, PIN6))
						{
							while(DIO_u8GetPinValue(PORTD, PIN6));
							switch(counter1)
							{
								case 0:
									flag_clear = 1;
									LCD_vidSendCommand(LCD_CLEAR);
									LCD_VidGotoRawCol(0,0);
									LCD_vidWriteString(" waiting put func");
									//put function
									put(PUT_BRING_STEPS);
									LCD_vidSendCommand(LCD_CLEAR);
									LCD_VidGotoRawCol(0,0);
									LCD_vidWriteString(" put func done");
									_delay_ms(5000);
									break;
							
								case 1 :
									flag_clear = 1;
									LCD_vidSendCommand(LCD_CLEAR);
									LCD_VidGotoRawCol(0,0);
									LCD_vidWriteString(" waiting bring fun");
									//bring function
									bring(PUT_BRING_STEPS);
									LCD_vidSendCommand(LCD_CLEAR);
									LCD_VidGotoRawCol(0,0);
									LCD_vidWriteString(" bring func done");
									_delay_ms(5000);
									break;
							
								case 2:
									flag--;
									counter1 = 0;
									break;
							}
						}
						break;
					
					case 2:
						if(1 == flag_clear)
						{
							flag_clear = 0;
							LCD_vidSendCommand(LCD_CLEAR);
							LCD_VidGotoRawCol(0,0);
							LCD_vidWriteString(" 1-rotate fwd");
							LCD_VidGotoRawCol(1,0);
							LCD_vidWriteString("2-rotate rvs");
							LCD_VidGotoRawCol(2,0);
							LCD_vidWriteString("3-back");
						
						}
						if(1 == DIO_u8GetPinValue(PORTD, PIN4))
						{
							while(DIO_u8GetPinValue(PORTD, PIN4));
							counter1--;
							if(counter1 < 0)
							{
								counter1 = 2;
							}
						}
						else if(1 == DIO_u8GetPinValue(PORTD, PIN5))
						{
							while(DIO_u8GetPinValue(PORTD, PIN5));
							counter1++;
							if(counter1 > 2)
							{
								counter1 = 0;
							}
						}
						LCD_VidGotoRawCol(counter1,0);
						if(1 == DIO_u8GetPinValue(PORTD, PIN6))
						{
							while(DIO_u8GetPinValue(PORTD, PIN6));
							switch(counter1)
							{
								case 0:
									flag_clear = 1;
									LCD_vidSendCommand(LCD_CLEAR);
									LCD_VidGotoRawCol(0,0);
									LCD_vidWriteString(" waiting rotF fun");
									//rotF function
									rotate_forward(PLACE1_5_STEPS);
									LCD_vidSendCommand(LCD_CLEAR);
									LCD_VidGotoRawCol(0,0);
									LCD_vidWriteString(" rotF func done");
									_delay_ms(5000);
									break;
							
								case 1 :
									flag_clear = 1;
									LCD_vidSendCommand(LCD_CLEAR);
									LCD_VidGotoRawCol(0,0);
									LCD_vidWriteString(" waiting rotR func");
									//rotR function
									rotate_reverse(PLACE1_5_STEPS);
									LCD_vidSendCommand(LCD_CLEAR);
									LCD_VidGotoRawCol(0,0);
									LCD_vidWriteString(" rotR func done");
									_delay_ms(5000);
									break;
							
								case 2:
									flag--;
									counter1 = 0;
									break;
							}
						}
						break;
					
					case 3:
					if(1 == flag_clear)
					{
						flag_clear = 0;
						LCD_vidSendCommand(LCD_CLEAR);
						LCD_VidGotoRawCol(0,0);
						LCD_vidWriteString(" 1-open door");
						LCD_VidGotoRawCol(1,0);
						LCD_vidWriteString("2-close door");
						LCD_VidGotoRawCol(2,0);
						LCD_vidWriteString("3-back");
						
					}
					if(1 == DIO_u8GetPinValue(PORTD, PIN4))
					{
						while(DIO_u8GetPinValue(PORTD, PIN4));
						counter1--;
						if(counter1 < 0)
						{
							counter1 = 2;
						}
					}
					else if(1 == DIO_u8GetPinValue(PORTD, PIN5))
					{
						while(DIO_u8GetPinValue(PORTD, PIN5));
						counter1++;
						if(counter1 > 2)
						{
							counter1 = 0;
						}
					}
					LCD_VidGotoRawCol(counter1,0);
					if(1 == DIO_u8GetPinValue(PORTD, PIN6))
					{
						while(DIO_u8GetPinValue(PORTD, PIN6));
						switch(counter1)
						{
							case 0:
								flag_clear = 1;
								LCD_vidSendCommand(LCD_CLEAR);
								LCD_VidGotoRawCol(0,0);
								LCD_vidWriteString(" waiting open func");
								//open function
								open_gate(OPEN_CLOSE_STEPS);
								LCD_vidSendCommand(LCD_CLEAR);
								LCD_VidGotoRawCol(0,0);
								LCD_vidWriteString(" up open done");
								_delay_ms(5000);
							break;
							
							case 1 :
								flag_clear = 1;
								LCD_vidSendCommand(LCD_CLEAR);
								LCD_VidGotoRawCol(0,0);
								LCD_vidWriteString(" waiting close func");
								//close function
								close_gate(OPEN_CLOSE_STEPS);
								LCD_vidSendCommand(LCD_CLEAR);
								LCD_VidGotoRawCol(0,0);
								LCD_vidWriteString(" down close done");
								_delay_ms(5000);
								break;
							
							case 2:
								flag--;
								counter1 = 0;
								break;
						}
					}
					break;
				}//switch
				
			}//else if
		}
			}
		else if(1 == read_down)
		{
			LCD_vidSendCommand(LCD_DISPLAY_ON);
			LCD_vidSendCommand(LCD_CLEAR);
			LCD_VidGotoRawCol(0,2);
			LCD_vidWriteString("    Automatic mode");
			while(1)
			{
			//automatic code	
			data = UART_voidRecieveData();
			//UART_voidSendData('$');
			
			switch (data)
			{
				case '0':  // asking about empty places
					if (counter < 8)
						UART_voidSendData('E');  // empty places
					else
						UART_voidSendData('F');  // full places
					_delay_ms(1000);
					UART_voidSendData('R');
					break;

				case '1':  // recieving car
					//Serial.println('1');
					if (counter >= 8)
					{
						UART_voidSendData('C');  // No empty places
						break;
					}
					to_origin();
					for (u8 i = 0; i < 8; i++)  //Searching for the nearest empty place
					{
						if (places[i].flag == 0)
						{
							/*************************?????3*******************************/
							GateSensorsBuffer = DIO_u8GetPinValue(GATE_OUT_SENSOR_PORT, GATE_OUT_SENSOR_PIN);
							
							if (GateSensorsBuffer == GATE_SENSORS_ACTIVE_VALUE) //A car found outside
							{
								open_gate(OPEN_CLOSE_STEPS);
								
								GateSensorsBuffer = DIO_u8GetPinValue(GATE_IN_SENSOR_PORT, GATE_IN_SENSOR_PIN);
								while (GateSensorsBuffer != GATE_SENSORS_ACTIVE_VALUE) //Waiting for car enterance
								{
									GateSensorsBuffer = DIO_u8GetPinValue(GATE_IN_SENSOR_PORT, GATE_IN_SENSOR_PIN);
									//???? ???? ?? ??? ??? ?????? ??? ??? ??? ???? ???????
								}
								
								
								_delay_ms(40000); //Waiting for driver going out
								close_gate(OPEN_CLOSE_STEPS);
							}
							else
							{
								UART_voidSendData('Z'); //No car outside
								break;
							}
							/*************************************************************/
							index++;
							temp = i + 48;
							UART_voidSendData(temp);  //The index of car position(To the DB)
							 //rtc
							if (i <= 3)  // To the first floor
							{
								parking(FLOOR_1, i);
								places[i].flag = 1; //To indicate a busy place
								break;
							}
							else  //To the second floor
							{
								parking(FLOOR_2, i);
								places[i].flag = 1; //To indicate a busy place
								break;
							}
						}
					}
					UART_voidSendData('D');
					stop();
					break;

				case '2':  //Taking car out
					//Serial.println('2');
					if (counter == 0)
					{
						UART_voidSendData('N');  //Empty garage
						UART_voidSendData('R');
						break;
					}
					index--;
					to_origin();
					UART_voidSendData('Y');
					/*_delay_ms(200);
					data = UART_voidRecieveData();*/
			
					 //data = NodeSerial.read();
					 //Serial.println(data);
					/*data = data - 48;
					UART_voidSendData(data + 48);*/
					
					data = serialParseInt();
					//UART_voidSendData(data);
					/*data = UART_voidRecieveData();*/
					//data = data - 48;
					if(index >7)
					{
					   // UART_sendString("data overflow");
						UART_voidSendData('O');
						break;
					}
					else
					{
						/*if(places[data].flag == 0)  //Empty place
						{
							//UART_sendString("data error");
							UART_voidSendData('e');
							break;
						}*/
						//places[data].flag = 0;
						places[index].flag = 0;
						if (index <= 3)  // to the first floor
						{
							retrieving(FLOOR_1, index);
							break;
						}
						else //To the second floor
						{
							retrieving(FLOOR_2, index - 4);
						}
					   // UART_sendString("Retrieving done");
						UART_voidSendData('D');
						stop();
					}
					break;

				case '3':
					up(FLOOR1_STEPS);
					stop();
					break;


				case '4':
					down(FLOOR1_STEPS);
					stop();
					break;

				case '5':
					rotate_forward(PLACE1_5_STEPS);
					stop();
					break;

				case '6':
					rotate_reverse(PLACE1_5_STEPS);
					stop();
					break;

				case '7':
					put(PUT_BRING_STEPS);
					stop();
					break;

				case '8':
					bring(PUT_BRING_STEPS);
					stop();
					break;

				case '9':
					stop();
					break;
		
				case '*':
					open_gate(OPEN_CLOSE_STEPS);
					break;
		
				case '#':
					close_gate(OPEN_CLOSE_STEPS);
					break;
			}
		}
		}
    }
}




void up(u16 step)
{
    for (int j = 0; j < step; j++)
    {

        DIO_VidSetPinValue(PORTB,UP_DOWN_1,HIGH);
        DIO_VidSetPinValue(PORTB,UP_DOWN_3,HIGH);
        _delay_us(period_up_down);


        DIO_VidSetPinValue(PORTB,UP_DOWN_1,LOW);
        DIO_VidSetPinValue(PORTB,UP_DOWN_2,HIGH);
        _delay_us(period_up_down);


        DIO_VidSetPinValue(PORTB,UP_DOWN_4,HIGH);
        DIO_VidSetPinValue(PORTB,UP_DOWN_3,LOW);
        _delay_us(period_up_down);


        DIO_VidSetPinValue(PORTB,UP_DOWN_1,HIGH);
        DIO_VidSetPinValue(PORTB,UP_DOWN_2,LOW);
        _delay_us(period_up_down);
        DIO_VidSetPinValue(PORTB,UP_DOWN_4,LOW);
        high--;
    }
}
void down(u16 step)
{
    for (int j = 0; j < step; j++)
    {
        DIO_VidSetPinValue(PORTB,UP_DOWN_4,HIGH);
        DIO_VidSetPinValue(PORTB,UP_DOWN_1,HIGH);
        _delay_us(period_up_down);

        DIO_VidSetPinValue(PORTB,UP_DOWN_1,LOW);
        DIO_VidSetPinValue(PORTB,UP_DOWN_2,HIGH);
        _delay_us(period_up_down);


        DIO_VidSetPinValue(PORTB,UP_DOWN_4,LOW);
        DIO_VidSetPinValue(PORTB,UP_DOWN_3,HIGH);
        _delay_us(period_up_down);


        DIO_VidSetPinValue(PORTB,UP_DOWN_1,HIGH);
        DIO_VidSetPinValue(PORTB,UP_DOWN_2,LOW);
        _delay_us(period_up_down);
        DIO_VidSetPinValue(PORTB,UP_DOWN_3,LOW);
        high++;
    }
}
void rotate_forward(u16 step)
{
    for (int j = 0; j < step; j++)
    {

        DIO_VidSetPinValue(PORTC,ROTATE_1,HIGH);
        DIO_VidSetPinValue(PORTC,ROTATE_3,HIGH);
        _delay_us(period_rotate);

        DIO_VidSetPinValue(PORTC,ROTATE_1,LOW);
        DIO_VidSetPinValue(PORTC,ROTATE_2,HIGH);
        _delay_us(period_rotate);

        DIO_VidSetPinValue(PORTC,ROTATE_4,HIGH);
        DIO_VidSetPinValue(PORTC,ROTATE_3,LOW);
        _delay_us(period_rotate);
        DIO_VidSetPinValue(PORTC,ROTATE_1,HIGH);
        DIO_VidSetPinValue(PORTC,ROTATE_2,LOW);
        _delay_us(period_rotate);
        DIO_VidSetPinValue(PORTC,ROTATE_4,LOW);
        angle++;


    }
}
void rotate_reverse(u16 step)
{

    for (int j = 0; j < step; j++)
    {

        DIO_VidSetPinValue(PORTC,ROTATE_4,HIGH);
        DIO_VidSetPinValue(PORTC,ROTATE_1,HIGH);
        _delay_us(period_rotate);

        DIO_VidSetPinValue(PORTC,ROTATE_1,LOW);
        DIO_VidSetPinValue(PORTC,ROTATE_2,HIGH);
        _delay_us(period_rotate);

        DIO_VidSetPinValue(PORTC,ROTATE_4,LOW);
        DIO_VidSetPinValue(PORTC,ROTATE_3,HIGH);
        _delay_us(period_rotate);
        DIO_VidSetPinValue(PORTC,ROTATE_1,HIGH);
        DIO_VidSetPinValue(PORTC,ROTATE_2,LOW);
        _delay_us(period_rotate);
        DIO_VidSetPinValue(PORTC,ROTATE_3,LOW);
        angle--;
    }
}
void bring(u16 step)
{

    for (int j = 0; j < step; j++)
    {

        DIO_VidSetPinValue(PORTA,PUT_BRING_1,HIGH);
        DIO_VidSetPinValue(PORTA,PUT_BRING_3,HIGH);
        _delay_us(period_put_bring);

        DIO_VidSetPinValue(PORTA,PUT_BRING_1,LOW);
        DIO_VidSetPinValue(PORTA,PUT_BRING_2,HIGH);
        _delay_us(period_put_bring);

        DIO_VidSetPinValue(PORTA,PUT_BRING_3,LOW);
        DIO_VidSetPinValue(PORTA,PUT_BRING_4,HIGH);
        _delay_us(period_put_bring);
        DIO_VidSetPinValue(PORTA,PUT_BRING_1,HIGH);
        DIO_VidSetPinValue(PORTA,PUT_BRING_2,LOW);
        _delay_us(period_put_bring);
        DIO_VidSetPinValue(PORTA,PUT_BRING_4,LOW);
        extension++;
    }
}
void put(u16 step)
{

    for (int j = 0; j < step; j++)
    {

        DIO_VidSetPinValue(PORTA,PUT_BRING_1,HIGH);
        DIO_VidSetPinValue(PORTA,PUT_BRING_4,HIGH);
        _delay_us(period_put_bring);

        DIO_VidSetPinValue(PORTA,PUT_BRING_1,LOW);
        DIO_VidSetPinValue(PORTA,PUT_BRING_2,HIGH);
        _delay_us(period_put_bring);

        DIO_VidSetPinValue(PORTA,PUT_BRING_3,HIGH);
        DIO_VidSetPinValue(PORTA,PUT_BRING_4,LOW);
        _delay_us(period_put_bring);
        DIO_VidSetPinValue(PORTA,PUT_BRING_1,HIGH);
        DIO_VidSetPinValue(PORTA,PUT_BRING_2,LOW);
        _delay_us(period_put_bring);
        DIO_VidSetPinValue(PORTA,PUT_BRING_3,LOW);
        extension--;

    }
}
void stop()
{
    DIO_VidSetPinValue(PORTB, UP_DOWN_1, LOW);
    DIO_VidSetPinValue(PORTB, UP_DOWN_2, LOW);
    DIO_VidSetPinValue(PORTB, UP_DOWN_3, LOW);
    DIO_VidSetPinValue(PORTB, UP_DOWN_4, LOW);

    DIO_VidSetPinValue(PORTC, ROTATE_1, LOW);
    DIO_VidSetPinValue(PORTC, ROTATE_2, LOW);
    DIO_VidSetPinValue(PORTC, ROTATE_3, LOW);
    DIO_VidSetPinValue(PORTC, ROTATE_4, LOW);

    DIO_VidSetPinValue(PORTA, PUT_BRING_1, LOW);
    DIO_VidSetPinValue(PORTA, PUT_BRING_3, LOW);
    DIO_VidSetPinValue(PORTA, PUT_BRING_2, LOW);
    DIO_VidSetPinValue(PORTA, PUT_BRING_4, LOW);
	
	DIO_VidSetPinValue(PORTA, OPEN_CLOSE1, LOW);
	DIO_VidSetPinValue(PORTA, OPEN_CLOSE2, LOW);
	DIO_VidSetPinValue(PORTA, OPEN_CLOSE3, LOW);
	DIO_VidSetPinValue(PORTA, OPEN_CLOSE4, LOW);
}
void parking(u8 floor, u8 place)
{

    put(PUT_BRING_STEPS);

    up(BRING_UP_DOWN_STEPS);

    bring(PUT_BRING_STEPS);
    down(floor_steps[floor] + BRING_UP_DOWN_STEPS);


    rotate_forward(place_steps[place]);

    put(PUT_BRING_STEPS);
    down(BRING_UP_DOWN_STEPS);
    bring(PUT_BRING_STEPS);
    up(BRING_UP_DOWN_STEPS + floor_steps[floor]);
    rotate_reverse(place_steps[place]);
    ++counter;




}
void retrieving(u8 floor, u8 place)
{
    down(floor_steps[floor] + BRING_UP_DOWN_STEPS);

    rotate_forward(place_steps[place]);

    put(PUT_BRING_STEPS);
    up(BRING_UP_DOWN_STEPS);
    bring(PUT_BRING_STEPS);
    up(floor_steps[floor] + BRING_UP_DOWN_STEPS);
    rotate_reverse(place_steps[place]);

    put(PUT_BRING_STEPS);
    down(BRING_UP_DOWN_STEPS);
    bring(PUT_BRING_STEPS);
	
	/***************************?????5****************************/
	open_gate(OPEN_CLOSE_STEPS);
	GateSensorsBuffer = DIO_u8GetPinValue(GATE_OUT_SENSOR_PORT, GATE_OUT_SENSOR_PIN);
	while (GateSensorsBuffer != GATE_SENSORS_ACTIVE_VALUE)
	{
		GateSensorsBuffer = DIO_u8GetPinValue(GATE_OUT_SENSOR_PORT, GATE_OUT_SENSOR_PIN);
	}
	_delay_ms(40000);
	close_gate(OPEN_CLOSE_STEPS);
	
	/*************************************************************/
    --counter;

}

void to_origin(void)
{
    up(high);
    rotate_reverse(angle);
    bring(extension);

}


u32 ctoi(u8 c)
{
    u8 result;
    result= c - 48;
    return  result ;
}


void close_gate(u16 step)
{
	for (int j = 0; j < step; j++)
	{

		DIO_VidSetPinValue(PORTA,OPEN_CLOSE1,HIGH);
		DIO_VidSetPinValue(PORTA,OPEN_CLOSE3,HIGH);
		_delay_us(period_open_close);


		DIO_VidSetPinValue(PORTA,OPEN_CLOSE1,LOW);
		DIO_VidSetPinValue(PORTA,OPEN_CLOSE2,HIGH);
		_delay_us(period_open_close);


		DIO_VidSetPinValue(PORTA,OPEN_CLOSE4,HIGH);
		DIO_VidSetPinValue(PORTA,OPEN_CLOSE3,LOW);
		_delay_us(period_open_close);


		DIO_VidSetPinValue(PORTA,OPEN_CLOSE2,LOW);
		DIO_VidSetPinValue(PORTA,OPEN_CLOSE1,HIGH);
		_delay_us(period_open_close);
		DIO_VidSetPinValue(PORTA,OPEN_CLOSE4,LOW);
	}
	stop();
}

void open_gate(u16 step)
{
	for (int j = 0; j < step; j++)
	{
		DIO_VidSetPinValue(PORTA,OPEN_CLOSE4,HIGH);
		DIO_VidSetPinValue(PORTA,OPEN_CLOSE1,HIGH);
		_delay_us(period_open_close);

		DIO_VidSetPinValue(PORTA,OPEN_CLOSE1,LOW);
		DIO_VidSetPinValue(PORTA,OPEN_CLOSE2,HIGH);
		_delay_us(period_open_close);


		DIO_VidSetPinValue(PORTA,OPEN_CLOSE4,LOW);
		DIO_VidSetPinValue(PORTA,OPEN_CLOSE3,HIGH);
		_delay_us(period_open_close);


		DIO_VidSetPinValue(PORTA,OPEN_CLOSE1,HIGH);
		DIO_VidSetPinValue(PORTA,OPEN_CLOSE2,LOW);
		_delay_us(period_open_close);
		DIO_VidSetPinValue(PORTA,OPEN_CLOSE3,LOW);
	}
	stop();
}