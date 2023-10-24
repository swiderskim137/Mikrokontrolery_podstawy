#include <avr/io.h>
#include <util/delay.h>
#define led1 (1<<PB6)
#define led2 (1<<PB7)
#define led3 (1<<PD5)
#define led4 (1<<PD6)
#define led5 (1<<PD7)


main(void){
	uint8_t v;
	ADMUX |= (1<<REFS0);// | (1<<REFS1);
	ADMUX |= (1<<MUX1) | (1<<MUX0);
    ADCSRA |= (1<<ADEN) | (1<<ADPS1) | (1<<ADPS2);
    DDRB |= (led1 | led2);
    DDRD |= (led3 | led4 | led5 );
    //DDRC &=~ (1<<PC3);

    //pomiar=pomiar(3);
    while(1){
    	_delay_ms(100);
    	ADCSRA |= (1<<ADSC);
    	while (ADCSRA & (1<<ADSC));
    	PORTB &= ~(led2 | led1);
    	PORTD &= ~(led3 | led4 | led5);

    	if (ADC>200){
    		PORTB |= led1;
    	}
    	if (ADC>400){
    		PORTB |= led2;
    	}
    	if (ADCW>600){
    		PORTD |= led3;
    	}
    	if (ADC>800){
    		PORTD |= led4;
    	}
    	if (ADC>1000){
    	    PORTD |= led5;
    	}
    }
}
