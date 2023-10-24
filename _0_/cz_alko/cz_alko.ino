const int analogPin = 0;
int odczyt = 0;//Odczytana wartość z ADC
float napiecie = 0;//Wartość przeliczona na napięcie w V

void setup() {
  Serial.begin(9600);
}

void loop() {
  odczyt = analogRead(analogPin);//Odczytujemy wartość napięcia
  napiecie = odczyt; //Przeliczenie wartości na napięcie
  Serial.println(napiecie);//Wysyłamy zmierzone napięcie
  delay(500);
}
