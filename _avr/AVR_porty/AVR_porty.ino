//ustawianie pinow jak w AVR
//na przykladzie mega

#define led13 (1<<PB7)
#define led13_ON PORTB |= led13
#define led13_OFF PORTB &= ~led13
#define led13_SW PORTB ^= led13


void setup() {
  Serial.begin(9600);
  Serial.println("start");

  DDRE |= (1<<PD4); // ustawienie pinu 2 jako wyjscie
  PORTE |= (1<<PD4);// ustawienie stanu wysokiego
  PORTE &= ~(1<<PD4);// ustawienie stanu niskiego

  //pin 7 jako wejście
  DDRH &= ~(1<<PH4);
  PORTH |= (1<<PH4); // podciągamy do vcc
  

  // pin 13 LED
  //DDRB |= (1<<PB7); // ustawienie pinu 13 jako wyjscie
  DDRB = 0b10000000;
  PORTB &= ~(1<<PB7);// ustawienie stanu niskiego

}

void blink1(int t){
  // ustawienie stanu wysokiego
  //PORTB |= (1<<PB7);
  //PORTB = 128;
  PORTB = 0b10000000;
  //PORTB = 0x80;
  delay(t);
  PORTB &= ~(1<<PB7);// ustawienie stanu niskiego
  delay(t);
}

void blink2(int t){
  PORTB ^=(1<<PB7);// zmiana stanu portu
  delay(t);
}

void blink3(int t){
  led13_ON;
  delay(t);
  led13_OFF;
  delay(t);
}

void blink4(int t){
  led13_SW;// zmiana stanu portu
  delay(t);
}



void loop() {
  //blink1(200);
  //blink2(1000);
  //blink3(100);
  //blink4(2000);
  if (!(PINH & (1<<PH4))) led13_ON;
  else led13_OFF;
  
}
