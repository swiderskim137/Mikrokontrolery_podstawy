#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//definicja LED1 (do kt�rego pinu pod��czony LED1)
#define s_g (1<<PB0)
#define warp_ladowanie (1<<PB1)
#define warp_blysk (1<<PB2)

#define wl_sg (1<<PB3)
#define warp (1<<PB4)
/*
 pin fun
in
 2 -- w�/wy� silnik�w g�
 3 -- w� procedury warp
out
 5 -- zasilanie silnika g�
 6 -- �adowanie kondensatora
 7 -- w� b�ysku

 */


uint8_t klawisz_on(uint8_t klawisz);
int main(void)
{
	//float T1=30;
	//int t1=(int)(T1*7.7);
	int mn=8,t2=5,t3=2;
	t2=t2*mn;
	t3=t3*mn;
	//########### I/O ###########
	 DDRB  |= (s_g | warp_ladowanie | warp_blysk);
	 //DDRB &= ~warp;
	 //DDRB &= ~wl_sg;

	 PORTB |= (s_g | wl_sg | warp);
	 //##########################
	 while(1){
		 if(klawisz_on(wl_sg))
		 {
			 PORTB ^= s_g;
			 _delay_ms (1000);
		 }

		 if(klawisz_on(warp))
		 {
			 PORTB |= warp_ladowanie;
			 for (int i=1; i<=t2;i++)
			 //�adowanie kondensatora i pojanienie silnik�w
			 {
				 _delay_ms (1000);
			 }
			 PORTB |= warp_blysk;
			 for (int i=1; i<=t3;i++)
			 //b�ysk silnik�w
			 {
				 _delay_ms (1000);
			 }
			 PORTB &= ~warp_blysk;
			 PORTB &= ~warp_ladowanie;
		 }
	 }

}

uint8_t klawisz_on(uint8_t klawisz)
{
	if  ( !((PINB) & klawisz) ){
				_delay_ms(100);
				if (!((PINB) & klawisz)) return 1;
	}
	return 0;
}
