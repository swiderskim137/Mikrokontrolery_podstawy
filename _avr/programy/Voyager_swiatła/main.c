#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//definicja LED1 (do kt�rego pinu pod��czony LED1)
#define LED1 (1<<PB1)

//definicja LED2 (do kt�rego pinu pod��czony LED2)
#define LED2 (1<<PB2)

#define warp (1<<PB4)
#define warp_on !(PINB & warp)

uint8_t klawisz_on(uint8_t klawisz);
int main(void)
{
	float T1=30;
	int t1=(int)(T1*7.7);
	int mn=8,t2=3,t3=5;
	t2=t2*mn;
	t3=t3*mn;
	//########### I/O ###########
	 DDRB  |= LED1 | LED2;
	 //PORTB |= LED2;
	 DDRB &= ~warp;
	 PORTB |= warp;
	 //##########################
	 while(1){
		 if(klawisz_on(warp))
		 {
			 PORTB |= LED1;
			 for (int i=1; i<=t3;i++)
			 {
				 _delay_ms (1000);
			 }
			 PORTB &= ~LED1;
		 }
	 }

}

uint8_t klawisz_on(uint8_t klawisz)
{
	if  ( !((PINB) & klawisz) ){
				_delay_ms(50);
				if (!((PINB) & klawisz)) return 1;
	}
	return 0;
}
