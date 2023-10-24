int odczyt = 0;//Odczytana wartość z ADC
float napiecie = 0;//Wartość przeliczona na napięcie w V

void setup() {
  Serial.begin(9600);//Uruchomienie komunikacji przez USART
  pinMode(13, OUTPUT);
}

void loop() {
  odczyt = analogRead(A0);//Odczytujemy wartość napięcia
  napiecie = odczyt * (5.0 / 1024.0); //Przeliczenie wartości na napięcie
  Serial.println(napiecie);//Wysyłamy zmierzone napięcie
  if (napiecie > 4.5) {
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
  }
  delay(1);//Czekamy, aby wygodniej odczytywać wyniki
}
