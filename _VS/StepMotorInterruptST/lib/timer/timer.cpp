#include "timer.h"
#include <Arduino.h>

void timer::timer1(int maxt)
{
    cli();      // stop interrupts
    TCCR1A = 0;
    TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10);
    OCR1A = 15624; // wartość porównania: 16 000 000 cykli zegara (1 s)
    //OCR1B = 1562; // wartość porównania: 16 000 000 cykli zegara (1 s)

    // ustawienie bitu OCIE1B (Output Compare B Match Interrupt Enable) w rejestrze TIMSK1
    // spowoduje wyzwolenie przerwania, gdy wartość licznika timera osiągnie wartość porównania OCR1B
    TIMSK1 |= (1 << OCIE1A);
    //TIMSK1 |= (1 << OCIE1B);
    sei();                   // allow interrupts
}

void timer::timer4(int maxt)
{
    cli();      // stop interrupts
    TCCR4A = 0; // set entire TCCR1A register to 0
    TCCR4B = 0; // same for TCCR1B
    TCNT4 = 0;  // initialize counter value to 0
    OCR4A = 10;//15624;// set compare match register
    //OCR4B = 15624;          // set compare match register
    TCCR4B |= (1 << WGM42); // turn on CTC mode
    TCCR4B |= (1 << CS42) | (1 << CS40);
    TIMSK4 |= (1 << OCIE4A); // enable timer compare interrupt
    //TIMSK4 |= (1 << OCIE4B);
    sei();                   // allow interrupts
}