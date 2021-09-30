#include<avr/io.h>
#include<avr/interrupt.h>
#include"util/delay.h"

unsigned char sec1 = 0 ;
unsigned char sec2 = 0 ;
unsigned char min1 = 0 ;
unsigned char min2 = 0 ;
unsigned char hour1 = 0 ;
unsigned char hour2 = 0 ;

void timer0_COMP_init()
{
    //prescaler 1024
	TCNT0=0;										      	
	TIMSK|=(1<<OCIE0);									
	TCCR0=(1<<FOC0)|(1<<CS02)|(1<<CS00)|(1<<WGM01);		
	OCR0=243;
	SREG|=1<<7;											
}


ISR(TIMER0_COMP_vect)
{
	sec1++;

	if(sec1>9)
	{
		sec1=0;
		sec2++;
	}
	if(sec2>=6)
	{
		min1++;
		sec1=0;
		sec2=0;
	}
	if(min1>9)
	{
		min2++;
		min1=0;
		sec1=0;
		sec2=0;
	}
	if(min2>=6)
	{
		hour1++;
		min2=0;
		min1=0;
		sec1=0;
		sec2=0;
	}
	if(hour1>9)
	{
		hour2++;
		hour1=0;
		min2=0;
		min1=0;
		sec1=0;
		sec2=0;
	}
	if(hour2 >12)				
	{
		TCNT1=0;
		sec1=0;
		sec2=0;
		min1=0;
		min2=0;
		hour1=0;
		hour2=0;
	}
}

void INT0_RESET()
{
	DDRD&=~(1<<PD2);			   	//PD2 as an input
	PORTD|=(1<<PD2);			  	//internal pull up resistor
	SREG|=1<<7;					     	//enable I BIT
	GICR|=(1<<INT0);			  	//enable external interrupt for interrupt 0
	MCUCR|=(1<<ISC01);				//falling edge
}


ISR(INT0_vect)
{
	
	sec1=0;
	sec2=0;
	min1=0;
	min2=0;
	hour1=0;
	hour2=0;

}

void INT1_PAUSE()
{
	DDRD&=~(1<<PD3);			      	 //pull down resistor
	SREG=1<<7;						         //enable I BIT
	GICR|=(1<<INT1);			       	//enable external interrupt for interrupt 1
	MCUCR|=(1<<ISC10)|(1<<ISC11);	//rising edge
}


ISR(INT1_vect)
{
	if(PIND&(1<<PD3))
		{

		TCCR0&=~(1<<FOC0)&~(1<<CS02)&~(1<<CS00)&~(1<<WGM01);
		}

}


void INT2_RESUME()
{
	DDRD&=~(1<<PB2);				//PB2 as an input
	PORTB|=(1<<PB2);				//internal pull up resistor
	GICR|=(1<<INT2);				//enable external interrupt for interrupt 2
	MCUCR&=~ (1<<ISC2); 			//falling edge because of pull up res
	SREG|=1<<7;					  	//enable I BIT
}


ISR(INT2_vect)
{
	if(!(PINB&(1<<PB2)))
	{

		TCCR0=(1<<FOC0)|(1<<CS02)|(1<<CS00)|(1<<WGM01);

	}

}


int main()
{
	DDRC|=0x0F;					//define the first 4 pins in portC as output pins
	PORTC&=0xF0;

	DDRA|=0x3F; 				//define the first 6 pins in portA 
	PORTA|=0X3F;

	INT0_RESET();
	INT1_PAUSE();
	INT2_RESUME();
	timer0_COMP_init();

	while(1)
		{
			
			// using multiplexed technique of 7 seg in order to use only the same PORTC 4  pins by enabling one segment 
			 
			PORTA=(1<<5);
			PORTC=sec1;
			_delay_ms(5);
			PORTA&=~(1<<5);

			PORTA|=(1<<4);
			PORTC=sec2;
			_delay_ms(5);
			PORTA&=~(1<<4);

			PORTA|=(1<<3);
			PORTC=min1;
			_delay_ms(5);
			PORTA&=~(1<<3);

			PORTA|=(1<<2);
			PORTC=min2;
			_delay_ms(5);
			PORTA&=~(1<<2);

			PORTA|=(1<<1);
			PORTC=hour1;
			_delay_ms(5);
			PORTA&=~(1<<1);

			PORTA|=(1<<0);
			PORTC=hour2;
			_delay_ms(5);
			PORTA&=~(1<<0);
		}
}
