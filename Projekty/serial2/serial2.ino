void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  Serial3.begin(9600);
  Serial.println("start0");
  Serial1.println("start1");
  Serial2.println("start2");
  Serial3.println("start3");
  
}

void loop() {
  Serial2.write("AT");
  delay(1000);
  if(Serial2.available()){
    if(Serial2.find("OK")) Serial.println("Polaczenie");
    //Serial.println("bufor ");
    //Serial.println(Serial2.readString());
  }else{
    Serial.println("blad");
  }
  delay(1000);
}
