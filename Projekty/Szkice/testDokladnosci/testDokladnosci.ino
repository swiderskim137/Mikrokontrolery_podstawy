void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("start");
}

  double a = 0.001;
  float b = 0.000009;
  float c = a+b;
  float w = 0; 
  double t = 0;
  double w2 = 0;

void loop() {

  for (int i=0; i < 1000; i++){
    w2=w2+a;
  }
  t+=1;
  Serial.print(t, 20);
  Serial.print("  ");
  Serial.print(w2, 20);
  Serial.print("  ");
  Serial.println(w2-t, 20);
  //Serial.println(w2, 20);
  delay(10);  
}
