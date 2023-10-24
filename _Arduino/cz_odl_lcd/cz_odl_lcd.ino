#include <LiquidCrystal.h>
#define trigPin 11
#define echoPin 12
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

void setup() {
  Serial.begin (9600);
  lcd.begin(16, 2); //Deklaracja typu
  pinMode(trigPin, OUTPUT); //Pin, do którego podłączymy trig jako wyjście
  pinMode(echoPin, INPUT); //a echo, jako wejście
}

void loop() {
  long odl, odl2;
  odl = odleglosc();
  if (odl != odl2) {
  //if (odl <=50){
    wys(odl);
    delay(500);}
  odl2 = odl;
}



void wys(long odl) {
  lcd.clear();
  if (odl < 10) {
    lcd.setCursor(8, 0);
  } else if (odl < 100) {
    lcd.setCursor(7, 0);
  } else if (odl < 1000) {
    lcd.setCursor(6, 0);
  } else {lcd.setCursor(5, 0);
  }
lcd.print(odl);
lcd.setCursor(6, 1);
lcd.print(" cm");
Serial.println(odl);
}

long odleglosc() {
  long czas;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  //Pomiar wykonany
  czas = pulseIn(echoPin, HIGH);
  return czas / 58;
}
