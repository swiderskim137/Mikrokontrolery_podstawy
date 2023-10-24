#include <avr/io.h>
#include <util/delay.h>

#define czeka (1<<PC5)
#define stycznik (1<<PB1)

#define czeka_swap PORTC ^= czeka
#define stycznik_swap PORTB ^= stycznik


int main(void){
DDRB |= stycznik;
DDRC |= czeka;
while(1){
czeka_swap;
stycznik_swap;
_delay_ms (50);}
}
