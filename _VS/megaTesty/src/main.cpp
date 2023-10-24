#include <Arduino.h>
#include <wypisywanie.h>
#include <wypisywanie2.h>

print wyp;
print2 wyp2;
void setup()
{
  Serial.begin(9600);
  Serial.println("start");
  wyp.kto();
  wyp2.kto();
}

int i = 0;

void loop()
{
  wyp.integer(i);
  i++;
  delay(1000);
}