#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//definicja LED1 (do kt�rego pinu pod��czony LED1)
#define LED1 (1<<PB6)

//definicja LED2 (do kt�rego pinu pod��czony LED2)
#define LED2 (1<<PB7)

//definicja pocz�tkowej warto�ci timera
#define timer_start 6

//zmienna pomocnicza-licznik u�ywana w przerwaniu
volatile uint8_t cnt=0;

void main(void)
{
 //########### I/O ###########
 DDRB  |= LED1 | LED2; //Ustawienie pin�w steruj�cych diodami
                                                  // jako wyj�cia
 PORTB |= LED1; //Ustawienie stanu wysokiego na wyj�ciu steruj�cym LED1
                                  //(stan pocz�tkowy)
 //##########################

 //######## konfiguracja timera ##############
 TIMSK |= (1<<TOIE0);           //Przerwanie overflow (przepe�nienie timera)
 TCCR0 |= (1<<CS02) | (1<<CS00); // �r�d�em CLK, preskaler 1024
 TCNT0 = timer_start;//          //Pocz�tkowa warto�� licznika
 //###########################################

 sei();//Globalne uruchomienie przerwa�

 while(1);//g��wna p�tla programu
 {

 }
}


//############ Procedura obs�ugi przerwania od przepe�nienia timera ############
ISR(TIMER0_OVF_vect)
{
  TCNT0 = timer_start;          //Pocz�tkowa warto�� licznika

  cnt++;     //zwi�ksza zmienn� licznik
  if(cnt>3)  //je�li 4 przerwania (czyli ok 1 s)
  {
    PORTB ^= LED1; //suma modulo 2 (XOR) stanu poprzedniego
                              //na porcie i pinu LED1 (zmiana stanu na przeciwny)

    PORTB ^= LED2; //suma modulo 2 (XOR) stanu poprzedniego na porcie
                             //pinu LED2 (zmiana stanu na przeciwny)
    cnt=0;     //zeruje zmienn� licznik
  }
}
//##############################################################################
