#include <Stepmot.h>
#include <Keypad.h>

Stepmot motor;

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
const int buttonSmin = 7;
const int buttonSm = 7;
const int buttonSp = 7;
const int buttonSmax = 7;
const int buttonPlus = A2;
const int buttonMinus = 7;

int sensorPin = A1; 
int sensorValue = 0;

int st = 0;
int i = 1;

void setup() {
  Serial.begin(9600);
  motor.init(4096, 2, 3, 4, 5);
  pinMode(buttonPlus, INPUT);
  pinMode(buttonMinus, INPUT);
  //void mot_mod(int number_of_steps);
  //void setSpeed(float time360);
  //void step(int this_step, int mod); // set position motor
  //void angle(float val); // 
  //void off();
}
int buttonState = 0;  
int ms = 1;
void loop() {
  char klawisz = klaw.getKey();
  if (klawisz) {
    Serial.println(klawisz); //wysyłanie na port com UART
    //Serial.println("---"); //wysyłanie na port com UART
    //Serial.println(klawisz); //wysyłanie na port com UART

    if (klawisz == 'A'){
      motor.setSpeed(1);}
    else if (klawisz == 'B'){
      ms -= 10;
      if (ms < 1) ms = 1;
      motor.setSpeed(ms);}
    else if (klawisz == 'C'){
      ms += 10;
      motor.setSpeed(ms);}
    else if (klawisz == 'D'){
      motor.setSpeed(60);}
    
    if (klawisz == '1'){
      motor.angle(1);}
    else if (klawisz == '3'){
      motor.angle(-1);}
    else if (klawisz == '4'){
      motor.angle(5);}
    else if (klawisz == '6'){
      motor.angle(-5);}
    else if (klawisz == '7'){
      motor.angle(10);}
    else if (klawisz == '9'){
      motor.angle(-10);}
   Serial.println(ms);
    delay(50);
  }
  
  buttonState = digitalRead(buttonPlus);
  if (buttonState == HIGH) {
    motor.angle(1);
  }
  buttonState = digitalRead(buttonMinus);
  if (buttonState == HIGH) {
    //motor.angle(-1);
  }

  //sensorValue = analogRead(sensorPin);
  //Serial.println(analogRead(sensorValue));
  
}
