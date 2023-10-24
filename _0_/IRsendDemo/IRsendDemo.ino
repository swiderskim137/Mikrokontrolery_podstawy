// IR Transmitter ...
#include <IRremote.h>

IRsend irsend;
int receiverpin = 2;
IRrecv irrecv(receiverpin);
decode_results results;

void setup()
{
  Serial.begin(9600);
  for (int i = 1; i <= 100; i++) {
    Serial.print("send ");
    Serial.println(i);
    irsend.sendNEC(0xE17A0CF3, 32);
    delay(2000);
  }
  for (int i = 1; i <= 100; i++) {
    Serial.print("send ");
    Serial.println(i);
    irsend.sendNEC(0xE17A8C73, 32);
    delay(2000);
  }
  irrecv.enableIRIn();
}

void loop() {
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
    irrecv.resume();
  }
  //Serial.println("send");
  //irsend.sendNEC(0xE17A9C63, 32);
  //delay(1000);
}
