#include <LiquidCrystal.h>
//#include <NewPing.h>
#define trigPin 11
#define echoPin 12
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
//NewPing sonar(trigPin, echoPin, 500);

void setup() {
  Serial.begin (9600);
  lcd.begin(16, 2); //Deklaracja typu
  pinMode(trigPin, OUTPUT); //Pin, do którego podłączymy trig jako wyjście
  pinMode(echoPin, INPUT); //a echo, jako wejście
}

void loop() {
  float odl;
  //odl = pomiar();
  //wys(srodl(5));
  //wys(pomiar());
  //delay(10);
  //odl = redukcja_zakl(10);
  wys(redukcja_zakl(10));
  //if (odl < 50) wys(odl);
}

float redukcja_zakl(int probka) {
  float dane[probka], sr = 0, mini = 1000;
  int n = probka;
  for (int i = 0; i < probka; i++) {
    dane[i] = pomiar();
    if (dane[i] < mini) mini = dane[i];
    //Serial.print(dane[i], 2);
    //Serial.print(" ");
  } //Serial.println();
  for (int i = 0; i < probka; i++) {
    if (dane[i] > mini * 2) {
      n--;
    } else {
      sr = sr + dane[i];
    }
    //Serial.print(dane[i],2);
    //Serial.print("  ");
  }
  return sr / n;
}

float srodl(float cykle) {
  float odl = 0;
  for (int i = 0; i < cykle; i++) {
    odl = odl + pomiar();
  }
  return odl / cykle;
}

void wys(float odl) {
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print(odl);
  Serial.println(odl);
}

float pomiar() {
  float czas;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  //unsigned int czas = sonar.ping();
  czas = pulseIn(echoPin, HIGH);
  return czas / 58;
}
