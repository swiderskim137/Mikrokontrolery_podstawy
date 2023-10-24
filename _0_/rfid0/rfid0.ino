#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 53
#define RST_PIN 49
MFRC522 rfid(SS_PIN, RST_PIN);
MFRC522 rfid2(47, RST_PIN);
MFRC522::MIFARE_Key key;

const byte UID[] = {0xD7, 0x59, 0x39, 0x4E};
boolean stan = false;



void setup() {
  pinMode(2,INPUT_PULLUP);
  pinMode(52, OUTPUT);
  pinMode(51, OUTPUT);
  pinMode(50, OUTPUT);
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  //Serial.print("aaaaa");
}

void loop() {
  if (digitalRead(7) == LOW) { //Jeśli przycisk wciśnięty
    MFRC522 rfid(47, RST_PIN);
  } else { //Jeśli warunek nie został spełniony (przycisk nie jest wciśnięty)
    MFRC522 rfid(53, RST_PIN);
  }
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial())
  {
    Serial.print("UID: {"); /*
    Serial.print(rfid.uid.uidByte[0] < 0x10 ? "" : "");
    Serial.print(rfid.uid.uidByte[0], HEX);
    Serial.print(rfid.uid.uidByte[1] < 0x10 ? "" : " ");
    Serial.print(rfid.uid.uidByte[1], HEX);
    Serial.print(rfid.uid.uidByte[2] < 0x10 ? "" : " ");
    Serial.print(rfid.uid.uidByte[2], HEX);
    Serial.print(rfid.uid.uidByte[3] < 0x10 ? " 0x0" : " 0x");
    Serial.print(rfid.uid.uidByte[3], HEX); */
    for (byte i = 0; i < rfid.uid.size; i++) {
      Serial.print(rfid.uid.uidByte[i] < 0x10 ? "0" : " ");
      Serial.print(rfid.uid.uidByte[i], HEX);
    }
    Serial.println("}");
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();


    if (rfid.uid.uidByte[0] == UID[0] &&
        rfid.uid.uidByte[1] == UID[1] &&
        rfid.uid.uidByte[2] == UID[2] &&
        rfid.uid.uidByte[3] == UID[3])
    {
      Serial.print("Poprawny\n");
      stan = true;
    } else
    {
      Serial.print("Niepoprawny\n");
      stan = false;
    }
  }
}
