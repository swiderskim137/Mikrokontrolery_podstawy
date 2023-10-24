#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//definicja LED1 (do którego pinu pod³¹czony LED1)
#define LED1 (1<<PB6)

//definicja LED2 (do którego pinu pod³¹czony LED2)
#define LED2 (1<<PB7)

//definicja pocz¹tkowej wartoœci timera
#define timer_start 6

//zmienna pomocnicza-licznik u¿ywana w przerwaniu
volatile uint8_t cnt=0;

void main(void)
{
 //########### I/O ###########
 DDRB  |= LED1 | LED2; //Ustawienie pinów steruj¹cych diodami
                                                  // jako wyjœcia
 PORTB |= LED1; //Ustawienie stanu wysokiego na wyjœciu steruj¹cym LED1
                                  //(stan pocz¹tkowy)
 //##########################

 //######## konfiguracja timera ##############
 TIMSK |= (1<<TOIE0);           //Przerwanie overflow (przepe³nienie timera)
 TCCR0 |= (1<<CS02) | (1<<CS00); // Ÿród³em CLK, preskaler 1024
 TCNT0 = timer_start;//          //Pocz¹tkowa wartoœæ licznika
 //###########################################

 sei();//Globalne uruchomienie przerwañ

 while(1);//g³ówna pêtla programu
 {

 }
}


//############ Procedura obs³ugi przerwania od przepe³nienia timera ############
ISR(TIMER0_OVF_vect)
{
  TCNT0 = timer_start;          //Pocz¹tkowa wartoœæ licznika

  cnt++;     //zwiêksza zmienn¹ licznik
  if(cnt>3)  //jeœli 4 przerwania (czyli ok 1 s)
  {
    PORTB ^= LED1; //suma modulo 2 (XOR) stanu poprzedniego
                              //na porcie i pinu LED1 (zmiana stanu na przeciwny)

    PORTB ^= LED2; //suma modulo 2 (XOR) stanu poprzedniego na porcie
                             //pinu LED2 (zmiana stanu na przeciwny)
    cnt=0;     //zeruje zmienn¹ licznik
  }
}
//##############################################################################
