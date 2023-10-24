//IR pin send in mega it is 9
//IR pin send in uno it is 3
#include <IRremote.h>
int receiverpin = 2;
IRrecv irrecv(receiverpin);
IRsend irsend;
decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop()
{
  //irsend.sendNEC(0xE17A9C63, 32);
  //delay(200);
  if (irrecv.decode(&results)) {
    if (results.decode_type == NEC) {
      Serial.print("NEC: ");
    } else if (results.decode_type == SONY) {
      Serial.print("SONY: ");
    } else if (results.decode_type == RC5) {
      Serial.print("RC5: ");
    } else if (results.decode_type == RC6) {
      Serial.print("RC6: ");
    } else if (results.decode_type == UNKNOWN) {
      Serial.print("UNKNOWN: ");
    }
    Serial.println(results.value, HEX);
    if (results.value == 0xE17A649B) {
      //Serial.println("send");
      delay(200);
      irsend.sendNEC(0xE17A9C63, 32);
      irrecv.enableIRIn();
    }
    delay(200);
    irrecv.resume();
  }
}
