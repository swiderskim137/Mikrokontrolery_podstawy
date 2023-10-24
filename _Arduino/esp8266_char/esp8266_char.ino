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
  //wyslij("AT+CWMODE=1","OK",100)) Serial.println("CWMODE=1 OK");
  wyslij2("AT+CWMODE=1", 100);
  wyslij2("AT+CIPMODE=0", 100); //) Serial.println("CIPMODE=0 OK");
  wyslij2("AT+CIPMUX=1", 100); //) Serial.println("CIPMUX=1 OK");
  //else Serial.println("CIPMUX=1 ERR");
  //wyslij2("AT+CWJAP=\"RANGER\",\"11235813\"",10000);
  wyslij2("AT+CWJAP=\"ESNET_35\",\"17777777\"", 5000); //)
  //AT+CWJAP="ESNET_35","17777777"
  //Serial.println("polaczono z siecia");
  wyslij2("AT+CIPSERVER=1,80", 2000); //) Serial.println("uruchomiono serwer");
  wyslij2("AT+CIFSR", 100);

  //strona = String();

}

char klient[10];
//char senval[10];
char bufor[30];
//char str1[100] = "<html><head><title>TEST</title></head><body><h2>";
//char str2[100] = "</h2></body></html>";
char strona[200];

void loop() {

  while (Serial2.available() > 0) {
    Serial.println("while");
    Serial.println(Serial2.readString());
    if (Serial2.find("+IPD,")) {
      Serial.println("if");
      Serial2.readBytesUntil(',', klient, 1);
      Serial.println();
      Serial.print("Zapytanie ID: ");
      Serial.println(klient[0]);
      //Serial.println(Serial2.readString());
      int sensorValue = analogRead(A0);
      //sprintf(senval, "%d", analogRead(A0));
      //strona = "<html><head><title>TEST</title></head><body><h2>test123</h2></body></html>";
      //<html><head><title>TEST</title></head></html>  45
      //<html><head><title>TEST</title></head><body><h2>123456789</h2></body></html> 76
      //Serial.println(senval);
      //Serial.println("xxx");
      //strona[200]="";
      //strcpy(strona,str1);
      //strcat(strona, senval);
      //Serial.println(strona);
      //strcat(strona, str2);
      sprintf(strona, "<html><head><title>TEST</title></head><body><h2>wartosc na A0: %d</h2></body></html>", sensorValue);
      //Serial.println(strona);
      //Serial.println(strlen(strona));
      sprintf(bufor, "AT+CIPSEND=%c,%d", klient[0], strlen(strona));
      if (wyslij(bufor, ">", 100)) Serial.println("zadanie wyslania");
      if (wyslij(strona, "OK", 100)) Serial.println("Wyslano dane");
      sprintf(bufor, "AT+CIPCLOSE=%c", klient[0]);
      if (wyslij(bufor, "OK", 10)) Serial.println("Zamknieto polaczenie");
    }
  }
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
