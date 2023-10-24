#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//out
#define s_g (1<<PD0)
#define warp_ladowanie (1<<PD1)
#define warp_blysk (1<<PD2)
#define s_imp (1<<PD3)
#define osw (1<<PD4)
#define mostek (1<<PD5)
#define def (1<<PD6)

#define wl_sg (1<<PB0)
#define warp (1<<PB1)
#define wl_s_imp (1<<PB2)
#define wl_osw (1<<PB3)
#define wl_mostka (1<<PB4)
#define wl_def (1<<PB5)
/*
 pin fun
in
 2 -- w³/wy³ silników g³
 3 -- w³ procedury warp
out
 5 -- zasilanie silnika g³
 6 -- ³adowanie kondensatora
 7 -- w³ b³ysku

 */


uint8_t klawisz_on(uint8_t klawisz);
int main(void)
{
	int mn=1,t2=5,t3=2;
	t2=t2*mn;
	t3=t3*mn;
	//########### I/O ###########
	 DDRD  |= (s_g | warp_ladowanie | warp_blysk | s_imp | osw | mostek | def);
	 PORTB |= (wl_sg | warp | wl_s_imp | wl_osw | wl_mostka | wl_def);
	 //##########################
	 while(1){
		 if(klawisz_on(wl_sg))
		 {
			 PORTD ^= s_g;
		 }
		 if(klawisz_on(wl_s_imp))
		 {
			 PORTD ^= s_imp;
		 }
		 if(klawisz_on(wl_osw))
		 {
			 PORTD ^= osw;
		 }
		 if (klawisz_on(wl_mostka))
		 {
			 PORTD ^= mostek;
		 }
		 if(klawisz_on(wl_def))
		 		 {
		 			 PORTD ^= def;
		 		 }
		 if(klawisz_on(warp))
		 {
			 PORTD |= warp_ladowanie;
			 for (int i=1; i<=t2;i++)
			 //³adowanie kondensatora i pojanienie silników
			 {
				 _delay_ms (1000);
			 }
			 PORTD |= warp_blysk;
			 for (int i=1; i<=t3;i++)
			 //b³ysk silników
			 {
				 _delay_ms (1000);
			 }
			 PORTD &= ~warp_blysk;
			 PORTD &= ~warp_ladowanie;
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
