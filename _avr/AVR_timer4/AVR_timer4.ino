//timer interrupts
//by Amanda Ghassaei adapted by T.Nilsson July 2019 :)
//June 2012
//https://www.instructables.com/id/Arduino-Timer-Interrupts/

/*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 3 of the License, or
* (at your option) any later version.
*
*/

//timer setup for timer4
//For arduino Mega

//timer4 will interrupt at 1Hz

//storage variables
//volatile boolean toggle4 = LOW;
//volatile int cycle = 0;

void setup(){
DDRB |= (1<<PB7); // ustawienie pinu 13 jako wyjscie
PORTB &= ~(1<<PB7);// ustawienie stanu niskiego
DDRH |= (1<<PH4); // ustawienie pinu 7 jako wyjscie
PORTH &= ~(1<<PH4);// ustawienie stanu niskiego
DDRH |= (1<<PH3); // ustawienie pinu 6 jako wyjscie
PORTH &= ~(1<<PH3);// ustawienie stanu niskiego

cli();//stop interrupts
//set timer4 interrupt at 1Hz
 TCCR4A = 0;// set entire TCCR1A register to 0
 TCCR4B = 0;// same for TCCR1B
 TCNT4  = 0;//initialize counter value to 0
 // set compare match register for 1hz increments
 int n = 15624;
 OCR4A = 15624;//15624/10;// = (16*10^6)fIC / (1*1024)(prescaler TCCRnB |= CSn2/1/0) = 15625-1 minus 1 bo porownuje od 0  == 1s (must be <65536)(max 16b val)
 OCR4B = 15624/10; //czas o jaki będzie przesuniete wykowywanie polecenia ISR(TIMER4_COMPB_vect){ wzgledem ISR(TIMER4_COMPA_vect){
 OCR4C = 15624/5;
 TCCR4B |= (1 << WGM42);// turn on CTC mode
 TCCR4B |= (1 << CS42) | (1 << CS40);// Set CS12 and CS10 bits for 1024 prescaler
 TIMSK4 |= (1 << OCIE4A);// enable timer compare interrupt
 TIMSK4 |= (1 << OCIE4B);// enable timer compare interrupt
 TIMSK4 |= (1 << OCIE4C);// enable timer compare interrupt
sei();//allow interrupts
}//end setup

ISR(TIMER4_COMPA_vect){
 PORTB ^=(1<<PB7);// pin 13 mega2560
 PORTB ^=(1<<PB7);// pin 13 mega2560
}

ISR(TIMER4_COMPB_vect){ //wykona się po ISR(TIMER4_COMPA_vect){ o czas zadeklarowany w OCR4B
 PORTH ^=(1<<PH4);// pin 7 mega2560
 PORTH ^=(1<<PH4);// pin 7 mega2560
}

ISR(TIMER4_COMPC_vect){//wykona się po ISR(TIMER4_COMPA_vect){ o czas zadeklarowany w OCR4C
 PORTH ^=(1<<PH3);// pin 6 mega2560
 PORTH ^=(1<<PH3);// pin 6 mega2560
}
 
void loop(){
}