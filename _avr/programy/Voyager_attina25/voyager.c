#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//definicja LED1 (do którego pinu pod³¹czony LED1)
#define LED1 (1<<PB1)

//definicja LED2 (do którego pinu pod³¹czony LED2)
#define LED2 (1<<PB2)

int main(void)
{
	//########### I/O ###########
	 DDRB  |= LED1 | LED2; //Ustawienie pinów steruj¹cych diodami
	                                                  // jako wyjœcia
	 PORTB |= LED2; //Ustawienie stanu wysokiego na wyjœciu steruj¹cym LED1
	                                  //(stan pocz¹tkowy)
	 //##########################
	 while(1){
		 _delay_ms (1000);
		 PORTB ^= LED1;
	 }

}
