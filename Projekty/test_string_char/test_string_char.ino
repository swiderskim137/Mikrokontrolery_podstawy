//#include <string>
void setup() {
  Serial.begin(9600);
  Serial.println("Start");
}
//String stronas;

void loop() {
  char *stronac;
  delay(1000);
  long int t = millis();
  Serial.println(t);
  sprintf(stronac, "<html><head><title>TEST</title></head><body><h2>%l</h2></body></html>", t);
  //stronas = stronac;
  //String stronas = String("<html><head><title>TEST</title></head><body><h2>"+"1");
  Serial.println(stronac);
}
