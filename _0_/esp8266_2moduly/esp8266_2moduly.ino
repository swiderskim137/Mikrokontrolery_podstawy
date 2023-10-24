//char str1[100], str2[100], strona[200];

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);
  Serial.println("Start");
  while (!wyslij("AT", "OK", 200))
  {
    Serial.println("Blad komunikacji");
    delay(1000);
  }
  Serial.println("Rozpoczeto komunikacje");
  wyslij2("AT+RST", 500);
  wyslij2("AT+CWMODE=3", 100);     //tryb pracy Klient-1, AP-2, APK-3
  wyslij2("AT+CIPMODE=0", 100);    //Tryb odbierania danych 0-(+IPD,kanał,l.bajtow) 1-na portszeregowy
  wyslij2("AT+CIPMUX=1", 100);     //liczba polaczen 0-jedno, 1-wiele
  //wyslij2("AT+CWJAP=\"ESNET_35\",\"17777777\"", 5000);
  //AT+CWJAP="ESNET_35","17777777"
  wyslij2("AT+CWSAP=\"ESP\",\"12345678\",5,3",2000);
  //AT+CWSAP="ESP","1234"
  wyslij2("AT+CIPSERVER=1,80", 2000);
  wyslij2("AT+CIFSR", 100); //zewnetrzne IP
  wyslij2("AT+CIPSTA?", 100); //lokalny IP Klient
  wyslij2("AT+CIPAP?", 100); //lokalny IP AP
}

//char klient[10];
//char bufor[30];
//char strona[200];

void loop() {
  while (Serial2.available() > 0) {
    Serial.println(Serial2.readString());}
/*
  while (Serial2.available() > 0) {
    if (Serial2.find("+IPD,")) {
      Serial2.readBytesUntil(',', klient, 1);
      Serial.println();
      Serial.print("Zapytanie ID: ");
      Serial.println(klient[0]);
      int sensorValue = analogRead(A0);
      sprintf(strona, "<html><head><title>TEST</title></head><body><h2>wartosc na A0: %d</h2></body></html>", sensorValue);
      sprintf(bufor, "AT+CIPSEND=%c,%d", klient[0], strlen(strona));
      if (wyslij(bufor, ">", 100)) Serial.println("zadanie wyslania");
      if (wyslij(strona, "OK", 100)) Serial.println("Wyslano dane");
      sprintf(bufor, "AT+CIPCLOSE=%c", klient[0]);
      if (wyslij(bufor, "OK", 10)) Serial.println("Zamknieto polaczenie");
    }
  }*/
}

boolean wyslij(String komenda, char *odp, int czas) {
  Serial2.println(komenda);
  long int time = millis();
  delay(czas);
  while (Serial2.available() > 0)
  {
    if (Serial2.find(odp))
      return 1;
  }
  return 0;
}

boolean wyslij2(String komenda, int czas) {
  String buf;
  Serial2.println(komenda);
  //long int time = millis();
  delay(czas);
  while (Serial2.available() > 0)
  {
    buf = Serial2.readString();
  }
  Serial.println(buf);
  if (buf == "OK") {
    return 1;
  }
  return 0;
}
