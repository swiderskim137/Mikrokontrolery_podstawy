void setup() {
Serial.begin(9600);
while(!Serial);
Serial.println("start");
}

int j=0;
void loop() {
  //if(Serial.available()) Serial.println("bufor");
  //if(Serial.findUntil("abc","-")) Serial.println("OK");
  if(Serial.available()){
    //j++;
    wyp_buf();
    //Serial.print(j);
  }
}

void wyp_buf()
{
  int n=Serial.available();
  char bufor[10];
  Serial.print(n);
  Serial.readBytes(bufor,n);
  //for (int i=1;i==n;i++){
    //Serial.print(i);
    Serial.print(bufor);
  //}
  //Serial.println(" koniec");
}
