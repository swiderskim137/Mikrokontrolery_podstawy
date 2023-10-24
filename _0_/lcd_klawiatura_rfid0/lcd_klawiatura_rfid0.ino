#include <LiquidCrystal.h> //Dołączenie bilbioteki
#include <Keypad.h> //biblioteka od klawiatury
#include <SPI.h>
#include <MFRC522.h>

//#define PIR 9 //czujnik ruchu
//+++++++++++++++++ RFID
#define SS_PIN 9
#define RST_PIN 8
MFRC522 rfid(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;

const byte UID[] = {0xD7, 0x59, 0x39, 0x4E};
boolean stan = false;

LiquidCrystal lcd(2, 3, 4, 5, 6, 7); //Informacja o podłączeniu nowego wyświetlacza
const byte ROWS = 4; // ile wierszy
const byte COLS = 4; //ile kolumn
byte rowPins[ROWS] = {45, 43, 41, 39}; //piny wierszy
byte colPins[COLS] = {37, 35, 33, 31}; //piny kolumn
char keys[ROWS][COLS] = { //mapowanie klawiatury
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
Keypad klaw = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); //inicjalizacja klawiatury

void setup() {
  lcd.begin(16, 2); //Deklaracja typu
  SPI.begin();
  rfid.PCD_Init();
  //pinMode(PIR, INPUT_PULLUP);
  //Serial.begin(9600); //Ustawienie prędkości transmisji
}

volatile int pozk = 0;

void loop() {
  char klawisz = klaw.getKey();

  if (rfid.PICC_IsNewCardPresent()) {
    if (rfid.PICC_ReadCardSerial())
    {
      lcd.setCursor(0, 0);
      Serial.print("UID: {");
      for (byte i = 0; i < rfid.uid.size; i++) {
        Serial.print(rfid.uid.uidByte[i] < 0x10 ? "0" : " ");
        Serial.print(rfid.uid.uidByte[i], HEX);
        lcd.print(rfid.uid.uidByte[i] < 0x10 ? "0" : " ");
        lcd.print(rfid.uid.uidByte[i], HEX);
      }
      Serial.println("}");
      //rfid.PICC_HaltA();
      //rfid.PCD_StopCrypto1();

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
    lcd.setCursor(1, 1);
    if (stan == true) {
      lcd.print("POPRAWNY");
    } else {
      lcd.print("BLEDNY");
    }
  }
  /*
    if (digitalRead(PIR) == HIGH) {
      ruch = 1;
    } else {
      ruch = 0;
    }
    if (ruch == zruch) {
      zruch = 0;
    } else {
      zruch = 1;
    }
    if (zruch == 1) {
      //lcd.clear();
      if (ruch == 1) {
        lcd.setCursor(0, 1);
        lcd.print("Wykrycie ruchu");
      } else {
        lcd.setCursor(0, 1);
        lcd.print("Brak ruchu    ");
      }
    }
    zruch = ruch;
  */
  //reset wyświetlacza
  if (klawisz) {
    //Serial.println(klawisz); wysyłanie na port com UART
    lcd.setCursor(12, 0);
    lcd.print(klawisz);
    delay(2000);
    lcd.clear();
  }
}
