#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//definicja LED1 (do kt�rego pinu pod��czony LED1)
#define LED1 (1<<PB1)

//definicja LED2 (do kt�rego pinu pod��czony LED2)
#define LED2 (1<<PB2)

int main(void)
{
	//########### I/O ###########
	 DDRB  |= LED1 | LED2; //Ustawienie pin�w steruj�cych diodami
	                                                  // jako wyj�cia
	 PORTB |= LED2; //Ustawienie stanu wysokiego na wyj�ciu steruj�cym LED1
	                                  //(stan pocz�tkowy)
	 //##########################
	 while(1){
		 _delay_ms (1000);
		 PORTB ^= LED1;
	 }

}
