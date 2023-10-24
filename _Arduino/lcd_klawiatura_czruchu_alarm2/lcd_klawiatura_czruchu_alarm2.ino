#include <LiquidCrystal.h> //Dołączenie bilbioteki
#include <Keypad.h> //biblioteka od klawiatury

#define PIR 47 //czujnik ruchu

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

int pinAlarmuPozycja = 1;
char pinCyfra1 = '1';
char pinCyfra2 = '2';
char pinCyfra3 = '3';
char pinCyfra4 = '4';
char klawisz = klaw.getKey();

void setup() {
  lcd.begin(16, 2); //Deklaracja typu
  pinMode(PIR, INPUT_PULLUP);
  //Serial.begin(9600); //Ustawienie prędkości transmisji
}
volatile int stanAlarmu = 1;
volatile int ruch = 0, zruch = 1;
volatile int pozk = 4;
volatile int zp = 1;
volatile int czas = 0;
volatile int zmp = 0;

void loop() {
  switch (stanAlarmu) { //Wykonywania akcji odpowiedniej dla danego stanu
    case 1:
      //Czuwanie
      lcd.setCursor(0, 0);
      lcd.print("Wlacz = A");
      //lcd.blink(); //Włącznie kursora
      pinAlarmuPozycja = 1;
      czas = 0;
      klawisz = klaw.getKey();
      if (klawisz == 'A') {
        stanAlarmu = 2;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Alarm Wlaczony");
        delay(1000);
        lcd.setCursor(0, 1);
        lcd.print("Wylacz = B");
        delay(1000);
      }
      break;

    case 2:
      //Monitorowanie
      klawisz = klaw.getKey();
      if (klawisz == 'B') {
        stanAlarmu = 3;
        czas = 0;
        lcd.clear();
      } else if (digitalRead(PIR) == HIGH) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Wykryto ruch !!!");
        delay(2000);
        stanAlarmu = 4;
        lcd.clear();
        pozk = 0;
      } else {
      }
      break;

    case 3:
      //Rozbrajanie
      lcd.setCursor(0, 0);
      lcd.print("PIN:");
      klawisz = klaw.getKey();
      if (klawisz) {
        //Czy kolejna podana cyfra jest poprawna?
        if (pinAlarmuPozycja == 1 && klawisz == pinCyfra1) { //Jesli sprawdzamy 1 pozycje PINu
          pinAlarmuPozycja++; //Cyfra poprawna, mozna sprawdzic na kolejna
          pozk = 5;
          lcd.setCursor(pozk, 0);
          lcd.print(klawisz);
        } else if (pinAlarmuPozycja == 2 && klawisz == pinCyfra2) { //Jesli sprawdzamy 2 pozycje PINu
          pinAlarmuPozycja++; //Cyfra poprawna, mozna sprawdzic na kolejna
          lcd.setCursor(++pozk, 0);
          lcd.print(klawisz);
        } else if (pinAlarmuPozycja == 3 && klawisz == pinCyfra3) { //Jesli sprawdzamy 3 pozycje PINu
          pinAlarmuPozycja++; //Cyfra poprawna, mozna sprawdzic na kolejna
          lcd.setCursor(++pozk, 0);
          lcd.print(klawisz);
        } else if (pinAlarmuPozycja == 4 && klawisz == pinCyfra4) { //Jesli sprawdzamy 4 pozycje PINu
          lcd.setCursor(++pozk, 0);
          lcd.print(klawisz);
          delay(500);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("PIN POPRWY");
          delay(2000);
          lcd.clear();
          stanAlarmu = 1; //Wszystkie 4 cyfry kodu sa poprawne
        } else {
          lcd.setCursor(0, 0);
          lcd.print("BLEDNY PIN !!!");
          delay(2000);
          lcd.clear();
          stanAlarmu = 4; //Blad w kodzie PIN - wlacz alarm
        }
      }
      czas++;
      delay(50);
      if (czas > 200) {
        stanAlarmu = 4;
        lcd.setCursor(0, 0);
        lcd.print("PRZEKROCZONY CZAS");
        delay(1000);
        lcd.clear();
      }
      break;

    case 4:
      //Sygnalizacja alarmu
      czas = 0;
      pinAlarmuPozycja = 1;
      if (pozk >= 7 ) {
        zp = -1;
      } else if (pozk <= 0 ) {
        zp = 1;
      }
      lcd.setCursor(pozk = pozk + zp, 0);
      lcd.print("! ALARM !");
      delay(400);
      klawisz = klaw.getKey();
      if (klawisz == 'B') {
        stanAlarmu = 3;
        lcd.clear();
      }
      break;
  }

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
      lcd.setCursor(14, 1);
      //lcd.print("Wykrycie ruchu");
      lcd.print("R1");
    } else {
      lcd.setCursor(14, 1);
      lcd.print("R0");
    }
  }
  zruch = ruch;
  //lcd.setCursor(13, 1);
  //lcd.print(zmp++);
  //if (zmp > 999) zmp = 0;
}
