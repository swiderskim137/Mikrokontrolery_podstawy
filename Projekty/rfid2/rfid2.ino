#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 53
#define RST_PIN 49
MFRC522 rfid(45, RST_PIN);
MFRC522 rfid2(47, RST_PIN);
MFRC522::MIFARE_Key key;

const byte UID[] = {0xD7, 0x59, 0x39, 0x4E};
boolean stan = false;



void setup() {
  pinMode(7, INPUT_PULLUP);
  pinMode(52, OUTPUT);
  pinMode(51, OUTPUT);
  pinMode(50, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(13,LOW);
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  //rfid2.PCD_Init();
  //Serial.print("aaaaa");
}

void loop() {
  if (digitalRead(7) == LOW) { //Jeśli przycisk wciśnięty
    digitalWrite(13,HIGH);
    if (rfid2.PICC_IsNewCardPresent() && rfid2.PICC_ReadCardSerial())
    {
      Serial.print("UID: {");
      for (byte i = 0; i < rfid2.uid.size; i++) {
        Serial.print(rfid2.uid.uidByte[i] < 0x10 ? "0" : " ");
        Serial.print(rfid2.uid.uidByte[i], HEX);
      }
      Serial.println("}");
      rfid2.PICC_HaltA();
      rfid2.PCD_StopCrypto1();
    }
  } else { //Jeśli warunek nie został spełniony (przycisk nie jest wciśnięty)
    digitalWrite(13,LOW);
    if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial())
    {
      Serial.print("UID: {");
      for (byte i = 0; i < rfid.uid.size; i++) {
        Serial.print(rfid.uid.uidByte[i] < 0x10 ? "0" : " ");
        Serial.print(rfid.uid.uidByte[i], HEX);
      }
      Serial.println("}");
      rfid.PICC_HaltA();
      rfid.PCD_StopCrypto1();
    }
  }
}
