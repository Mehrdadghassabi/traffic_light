/*
 * tl.c
 *
 * Created: 06/26/2022 06:38:03 ب.ظ
 * Author : Mehrdad
 */ 

#include <avr/io.h>
#define F_CPU 4000000UL
#include <util/delay.h>
#include <stdio.h>
void ADC_Init()
{
	/*
	Thanks to https://www.electronicwings.com/avr-atmega/atmega1632-adc
	*/
	DDRA=0x0;			/* Make ADC port as input */
	ADCSRA = 0x87;			/* Enable ADC, fr/128  */
	ADMUX = 0x40;			/* Vref: Avcc, ADC channel: 0 */
	
}

int ADC_Read(char channel)
{
	/*
	Thanks to https://www.electronicwings.com/avr-atmega/atmega1632-adc
	*/
	
	int Ain,AinLow;
	
	ADMUX=ADMUX|(channel & 0x0f);	/* Set input channel to read */

	ADCSRA |= (1<<ADSC);		/* Start conversion */
	while((ADCSRA&(1<<ADIF))==0);	/* Monitor end of conversion interrupt */
	
	_delay_us(10);
	AinLow = (int)ADCL;		/* Read lower byte*/
	Ain = (int)ADCH*256;		/* Read higher 2 bits and 
					Multiply with weight */
	Ain = Ain + AinLow;				
	return(Ain);			/* Return digital value*/
}

main()
{
	int value; //int to store ADC value
	int delay_time = 150;
	DDRD|=(1<<0)|(1<<1)|(1<<3)|(1<<4)|(1<<6)|(1<<7);
	DDRC|=(1<<0);
    //PORTD = 0b00000000;
	while (1)
	{
		    ADC_Init();
			
			value = ADC_Read(0);

			
			 PORTD = (1<<0)|(1<<1);
			 for(int k=0 ; k<value ; k++){
			_delay_ms(1);}
			
			PORTD = (1<<3)|(1<<4);
			_delay_ms(1000);
			
			PORTD = (1<<6)|(1<<7);
			for(int k=0 ; k<1000-value ; k++){
			_delay_ms(1);}
		

	}

	return 0;
}

