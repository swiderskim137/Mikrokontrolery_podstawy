//IR pin send in mega it is 9
//IR pin send in uno it is 3
#include <IRremote.h>
#define diodaPIN 3
int receiverpin = 2;
int wypelnienie = 30;
IRrecv irrecv(receiverpin);
IRsend irsend;
decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn();
  pinMode(diodaPIN, OUTPUT);
}

void loop()
{
  /*
  irsend.sendNEC(0x11111111, 32);
  irrecv.enableIRIn();
  analogWrite(diodaPIN, wypelnienie);
  //Serial.println("strzal");
  delay(200);
  analogWrite(diodaPIN, 0);
  */
  
  if (irrecv.decode(&results)) {
    //Serial.println(results.value, HEX);
    if (results.value == 0x11111111) {
      analogWrite(diodaPIN, 30);
      Serial.println(results.value, HEX);
      delay(1000);
      analogWrite(diodaPIN, 0);
    }
    delay(100);
    irrecv.resume();
  }
  //*/
}
