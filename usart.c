/*
 * UART.c
 *
 * Created: 11/4/2019 8:35:58 AM
 *  Author: mjmca
 */ 

#include "usart.h"
#include <avr/io.h>

void init_usart(void)
{
	uint8_t BSel = 234;
	uint8_t BScale = -4;
	
	PORTD_OUTSET = PIN3_bm;
	PORTD_DIRSET = PIN3_bm;
	PORTD_DIRCLR = PIN2_bm;
	USARTD0_CTRLB = (PIN4_bm | PIN3_bm);
	USARTD0_CTRLC = (PIN1_bm | PIN0_bm);
	USARTD0.CTRLA = PIN4_bm;
	USARTD0_BAUDCTRLA = (BSel & 0XFF);
	USARTD0_BAUDCTRLB = (((BScale << 4) & 0xF0) | ((BSel >> 8) & 0X0F));
	
}

void usart_out_char(char c)
{
	while(!(USARTD0_STATUS & PIN5_bm));
	USARTD0_DATA = c;
}

char usart_in_char(void)
{
	while(!(USARTD0_STATUS & PIN7_bm));
	uint8_t temp = USARTD0_DATA;
	return temp;
	
}

char * usart_in_string()
{
    char *charArray = malloc (100 * sizeof (char));
	int i  = 0;
	while(1)
	{
		
		char temp = usart_in_char();
		int len = strlen(charArray);
	
		if(temp ==  0x08 | temp == 0x1B)
		{
			i--;
		}
		else
		{
			charArray[i+1] = charArray[i];
			charArray[i] = temp;
			if(temp == 0x0D){
				break;
			}
			i++;
		}
	}
	return charArray;
}

void usart_out_string(char * temp)
{
	while(*temp != 0x0D){
		usart_out_char(*temp);
		temp++;
	}
}

