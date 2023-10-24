#define diodaPIN 45

int wypelnienie = 30;
int zmiana = 5;
int ile = 5;
int z = 0;
float n = PI / 180;

void setup() {
  Serial.begin(9600);
  pinMode(diodaPIN, OUTPUT); //Konfiguracja pinu 13 jako wyjście
  //pinMode(52, INPUT_PULLUP);
  //zamigajLED(500, 5);
  analogWrite(diodaPIN, wypelnienie);
}

void loop() {
  //zamigajLED();
  //pwmsin(50);
  //zamigajLED(100,5);
  //if (digitalRead(52) == LOW) zamigajLED(500,5);
}

void zamigajLED(int czas, int ile) {
  for (int i = 0; i < ile; i++) {
    digitalWrite(diodaPIN, HIGH); //Włączenie diody
    delay(czas); //Odczekanie jakiegoś czasu
    digitalWrite(diodaPIN, LOW); //Wyłączenie diody
    delay(czas); //Odczekanie jakiegoś czasu
  }
}

void pwm(int czas) {
  analogWrite(diodaPIN, wypelnienie); //Generujemy sygnał o zadanym wypełnieniu
  if (z == 0) {
    wypelnienie = wypelnienie + zmiana;
    if (wypelnienie >= 255) z = 1;
  } else if (z == 1) {
    wypelnienie = wypelnienie - zmiana;
    if (wypelnienie <= 0) z = 0;
  }
  Serial.println(wypelnienie);
  delay(czas); //Małe opóźnienie, aby efekt był widoczny
}

void pwmsin(int czas) {
  analogWrite(diodaPIN, wypelnienie); //Generujemy sygnał o zadanym wypełnieniu
  if (z > 360) {
    z = 0;
  }
  wypelnienie = (sin(z*n)*255+255)/2;
  z++;
  Serial.println(wypelnienie);
  //Serial.println(sin(z*n));
  delay(czas); //Małe opóźnienie, aby efekt był widoczny
}

void zamigajLED() {
  digitalWrite(13, HIGH); //Włączenie diody
  delay(500); //Odczekanie 0,5 sekundy
  digitalWrite(13, LOW); //Wyłączenie diody
  delay(500); //Odczekanie 0,5 sekundy
}
