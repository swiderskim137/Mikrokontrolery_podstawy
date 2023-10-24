//1-gnd
//2-vcc
//3-1.6k-gnd
//4-pin
//5-gnd
//6-pin
//11,14-pin
//15-vcc
//16-gnd
#include <LiquidCrystal.h> //Dołączenie bilbioteki
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); //Informacja o podłączeniu nowego wyświetlacza

void setup() {
  lcd.begin(16, 2); //Deklaracja typu
  lcd.setCursor(2, 0); //Ustawienie kursora
  lcd.print("WESOLYCH"); //Wyświetlenie tekstu
  lcd.setCursor(3, 1); //Ustawienie kursora
  lcd.print("SWIAT!"); //Wyświetlenie tekstu
  lcd.setCursor(12, 1);
  lcd.print(150);
  //lcd.blink(); //Włącznie kursora
}

void loop() {
  //lcd.noDisplay(); //Wyłącz i poczekaj
  //delay(500);
  //lcd.clear()
  lcd.setCursor(12, 2);
  lcd.print(":-D");
  delay(1000);
  lcd.setCursor(12, 2);
  lcd.print(":-)"); //Wyświetlenie tekstu
  //lcd.display(); //Włącz i poczekaj
  delay(1000);
}
