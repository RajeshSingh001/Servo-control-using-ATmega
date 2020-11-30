#include "light.h"
#include <util/delay.h>
#include <avr/interrupt.h>

int photo[8];

void init_timer1(){
	//top=20000, prescaler=8, frec=50hz (T=20ms)
	ICR1=20000;
	TCCR1B|=_BV(CS11);
	
	//phase and frequency correction, icr1 = top
	TCCR1B|=_BV(WGM13);
	//set OC1A,OC2B on downcounting, clear on upcounting
	TCCR1A|=_BV(COM1A1)|_BV(COM1B1);
	//output pins, PORTD4 (motor 2) and PORTD5 (motor 1)
	DDRD|=_BV(4)|_BV(5);
	
	//default position
	OCR1A=1000;
	OCR1B=1000;
	
}


int get_pulse1(int degrees){
//get the pulse for the bottom motor
	if(degrees>180)
		degrees-=180;	
	return get_pulse2(degrees);	
}

void set_pulse1(int degrees){
	OCR1A=get_pulse1(degrees);
}

int get_pulse2(int degrees){
	return (int)((float)degrees*1000/180+1000);
}

void set_pulse2(int degrees){
	OCR1B=get_pulse2(degrees);
}

int ADC_get(uint8_t channel)
{

	ADMUX &= 0xE0;
	
	ADMUX |= channel;
	ADCSRA |= _BV(ADEN)|_BV(ADSC);
	while(!(ADCSRA & (1<<ADIF)));
	return ADC;
}

void ADC_init(void)
{
	// AVCC with capacitor on AREF;
	// PA7 as input single ended; result left-adjusted (8 bit data)
	ADMUX = (1<<REFS0) | (1<<MUX1);
	// max prescaler
	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);

}

int main(void){
	int i;
	init_timer1();
	while(1){
		set_pulse1(0);
		set_pulse2(180);
		for(i=1;i<10;i++)
			_delay_ms(300);
		set_pulse2(0);
		set_pulse1(180);
		for(i=1;i<10;i++)
			_delay_ms(300);
	}
	return 0;
}
