#include <avr/io.h>
#include <util/delay.h>

#define eng (1<<PB3)
#define warp (1<<PB2)
#define warp_blysk (1<<PB1)
#define eng_on PORTB |= eng
#define eng_off PORTB &= ~eng
#define eng_swap PORTB ^= eng
#define warp_on PORTB |= warp
#define warp_off PORTB &= ~warp
#define warp_swap PORTB ^= warp
#define key_warp (1<<PB6)
#define key_eng (1<<PB7)

uint8_t klawisz_on(uint8_t klawsz);
int main(void){
	DDRB = 0x0e;
	PORTB |= (1<<PB6);
	PORTB |= (1<<PB7);
	_delay_ms(3000);
	eng_on;
	while(1){
		if (klawisz_on(key_eng)){
			eng_swap;
			_delay_ms( 200 );
		}
		if (klawisz_on(key_warp)){
			_delay_ms(500);
			PORTB |= warp_blysk;
			_delay_ms(500);
			PORTB &= ~warp_blysk;
			warp_swap;
			_delay_ms( 200 );
		}
	}
}

uint8_t klawisz_on(uint8_t klawsz)
{
	if  ( !(PINB & klawsz) ){
				_delay_ms(50);
				if (!(PINB & klawsz)) return 1;
	}
	return 0;
}
