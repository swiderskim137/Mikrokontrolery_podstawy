unsigned long aktualnyCzas = 0;
unsigned long zapamietanyCzas = 0;
unsigned long roznicaCzasu = 0;
int x = 0, y = 0, z = 0, l = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("start");
}
//aktualnyCzas = millis();
void loop() {
  l = l + 1;
  if (x < 1000) {
    x = x + 1;
  }else {
    Serial.println(millis());
    Serial.println(l);
  }
}
