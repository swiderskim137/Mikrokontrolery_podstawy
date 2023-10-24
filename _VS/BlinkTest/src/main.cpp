#include <Arduino.h>

void setup()
{
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("Start");
}

// the loop function runs over and over again forever
int i = 0;
void loop()
{
  digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
  delay(1000);                     // wait for a second
  digitalWrite(LED_BUILTIN, LOW);  // turn the LED off by making the voltage LOW
  delay(1000);                     // wait for a second
  Serial.println(i);
  i++;
}