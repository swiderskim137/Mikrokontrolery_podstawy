#include <LiquidCrystal.h>
#define trigPin 10
#define echoPin 11
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
  /*if (odl != odl2) {
    wys(odl);
    delay(500);
  }
  odl2 = odl;
  */
  Serial.println(odl);
  wys(odl);
  delay(200);
}

void wys(long odl) {
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print(odl);
  lcd.print(" cm");
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
