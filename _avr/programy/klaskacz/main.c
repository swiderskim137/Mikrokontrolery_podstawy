#include <avr/io.h>
#include <util/delay.h>
//in
#define ruch (1<<PB0)
#define sygnal (1<<PB2)
#define czas (1<<PB1)
//#define czas_dzia³ania (1<<)
//out
#define czeka (1<<PB3)
#define stycznik (1<<PB4)
#define czeka_swap PORTB ^= czeka
#define czeka_on PORTB |= czeka
#define czeka_off PORTB &= ~czeka
#define stycznik_swap PORTB ^= stycznik
#define stycznik_on PORTB |= stycznik
#define stycznik_off PORTB &= ~stycznik

uint8_t klawisz_on(uint8_t klawisz);

int main(void){
	uint8_t t=1;
	uint8_t tryb=1;
	//1=klaskacz 2=czujnik ruchu z wyl przez klaniêcie
	//3=czujnik ruchu czasowe w³
DDRB |= (1<<PB3);
DDRB |= (1<<PB4);
PORTB |= sygnal;
PORTB |= czas;
//PORTB |= czas_dzialania;
//PORTB |= (1<<PB0);

while(1){
/////////////////////////////
	if (klawisz_on(czas)){
			tryb=tryb+1;
			_delay_ms (200);
			if (tryb>2){
						tryb=1;
						czeka_on;
						_delay_ms (1000);
						czeka_off;
						_delay_ms (200);
					}
	}

/*////////////////////////////
	if (klawisz_on(czas)){
		t=t+1;
		_delay_ms (200);
		if (t>5){
			t=1;
			czeka_on;
			_delay_ms (1000);
			czeka_off;
			_delay_ms (200);
		}
		for (int j=1;j<=t;j++){
					czeka_on;
					_delay_ms (100);
					czeka_off;
					_delay_ms (100);
				}
	}
*/////////////////////////////
	if (klawisz_on(sygnal)){
		czeka_swap;
		_delay_ms (200);
		for (int i=1;i<=t*100;i++){
			_delay_ms (10);
			if (klawisz_on(sygnal)){
				stycznik_swap;
				i=3000;
				_delay_ms (200);
			}

		}
		czeka_off;
	}
/////////////////////////////
	if ( (tryb == 2) && !klawisz_on(ruch)){
		stycznik_on;
	}
/////////////////////////////
}
}

uint8_t klawisz_on(uint8_t klawisz)
{
	if  ( !(PINB & klawisz) ){
				_delay_ms(50);
				if (!(PINB & klawisz)) return 1;
	}
	return 0;
}
