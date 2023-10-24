#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h> //Dołączenie bilbioteki

#define SS_PIN 8
#define RST_PIN 9
#define trigPin 11
#define echoPin 12
MFRC522 rfid(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;

LiquidCrystal lcd(2, 3, 4, 5, 6, 7); //Informacja o podłączeniu nowego wyświetlacza
//const byte UID[] = {0xD7, 0x59, 0x39, 0x4E};
//boolean stan = false;

void setup() {
  lcd.begin(16, 2); //Deklaracja typu
  pinMode(A2, INPUT_PULLUP);
  //pinMode(11, OUTPUT);
  //pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  lcd.setCursor(0, 0);
  pinMode(trigPin, OUTPUT); //Pin, do którego podłączymy trig jako wyjście
  pinMode(echoPin, INPUT); //a echo, jako wejście
  //Serial.print("aaaaa");
  //lcd.print("abc");
}
int n = 1, k = 0;
void loop() {
  long odl = 1;
  if (digitalRead(A2) == LOW) {
    lcd.clear();
    odl=odleglosc();
    wys(odl);
    delay(500);
  } else if (digitalRead(A2) == HIGH)  {
    digitalWrite(trigPin, LOW);
    if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial())
    {
      if (k == 0) {
        lcd.setCursor(0, 0);
        k++;
      } else if (k == 1) {
        lcd.setCursor(0, 1);
        k--;
      }
      //lcd.clear();
      //lcd.setCursor(0, 1);
      lcd.print(n);
      n++;
      lcd.print(":");
      for (byte i = 0; i < rfid.uid.size; i++) {
        lcd.print(rfid.uid.uidByte[i] < 0x10 ? "0" : " ");
        lcd.print(rfid.uid.uidByte[i], HEX);
        Serial.print(rfid.uid.uidByte[i] < 0x10 ? "0" : " ");
        Serial.print(rfid.uid.uidByte[i], HEX);
      }
      lcd.print(" ");
      lcd.print(rfid.uid.size);
      rfid.PICC_HaltA();
      rfid.PCD_StopCrypto1();
    }
  }
}

void wys(long odl) {
  lcd.clear();
  if (odl < 10) {
    lcd.setCursor(8, 0);
  } else if (odl < 100) {
    lcd.setCursor(7, 0);
  } else if (odl < 1000) {
    lcd.setCursor(6, 0);
  } else {
    lcd.setCursor(5, 0);
  }
  lcd.print(odl);
  lcd.setCursor(6, 1);
  lcd.print(" cm");
  Serial.println(odl);
}

long odleglosc() {
  long czas;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  //Pomiar wykonany
  czas = pulseIn(echoPin, HIGH);
  return czas / 58;
}
