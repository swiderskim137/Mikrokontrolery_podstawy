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

}

void loop() {
  // put your main code here, to run repeatedly:

}

boolean wyslij(String komenda, char *odp, int czas) {
  Serial2.println(komenda);
  delay(czas);
  while (Serial2.available() > 0)
  {
    if (Serial2.find(odp))
      return 1;
  }
  return 0;
}
