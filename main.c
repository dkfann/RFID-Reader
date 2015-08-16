/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>
#include "avr.h"
#include "lcd.h"
#include <stdio.h>
#include <string.h>
#include "uart.h"

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	
	board_init();
	ini_lcd();
	clr_lcd();
	char *sp = "A";
	unsigned char *id = "A";
	unsigned char *id2 = "A";
	unsigned char *a = "A";
	unsigned char b = "B";
	char buffer[10];
	char buffer2[10];
	SET_BIT(DDRA,0);
	//SET_BIT(PORTA,0);
	CLR_BIT(PORTA,0);
	
	SET_BIT(DDRA,1);
	SET_BIT(DDRA,2);
	SET_BIT(DDRA,3);
	SET_BIT(DDRA,4);
	CLR_BIT(DDRA,5);
	
	CLR_BIT(PORTA,1);
	CLR_BIT(PORTA,2);
	CLR_BIT(PORTA,3);
	
	
	CLR_BIT(DDRC,0);
	SET_BIT(PORTC,0);
	
	SET_BIT(ADMUX, REFS0);
	CLR_BIT(ADMUX, REFS1);
	ADMUX |= 0x04;
	ADCSRA = (1 << ADEN);
	unsigned long sample = 0;
	int check = 0;
	char *ch = "A";
	uart_init();
	
	for(;;)
	{
		CLR_BIT(PORTA,0);
		//SET_BIT(PORTA,0);
		sample = get_sample();
		CLR_BIT(PORTA,1);
		CLR_BIT(PORTA,2);
		if(sample >= 7)
		{
			pos_lcd(1,0);
			wait_avr(500);
			for(int i = 0; i < 4; i++)
			{
				wait_avr(300);
				a=uart_recieve();                   // save the received data in a variable
				itoa(a,buffer,10);                  // convert numerals into string
				buffer2[i] = buffer[0];
				put_lcd(buffer2[i]);
			}
			buffer2[4] = 0;
			if(strcmp(buffer2, "6101") == 0)
			{
				SET_BIT(PORTA,2);
				SET_BIT(PORTA,0);
			}
			else if(strcmp(buffer2, "6111") == 0)
			{
				CLR_BIT(PORTA,2);
				SET_BIT(PORTA,1);
				CLR_BIT(PORTA,0);
			}			
			wait_avr(2500);
		}
		else if(sample < 7)
		{
			clr_lcd();
			CLR_BIT(PORTA,1);
			CLR_BIT(PORTA,2);
			CLR_BIT(PORTA,3);
		}	
	}
}
