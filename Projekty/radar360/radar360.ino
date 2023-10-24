#include <SPI.h>
#include <Wire.h>
#include <Stepmot.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define trigPin 6
#define echoPin 7
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Stepmot motor;

long odl;
long data_skan[360][2];

void setup() {
  Serial.begin (9600);
  motor.init(4096, 2, 3, 4, 5);
  motor.angle(360);
  motor.setSpeed(60);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  pinMode(trigPin, OUTPUT); //Pin, do którego podłączymy trig jako wyjście
  pinMode(echoPin, INPUT); //a echo, jako wejście
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(2, 2);
  display.display();

  wys();
  motor.off();
}



void loop() {
  //skan();
  //wys();
}

void wys() {
  display.drawLine(display.width() / 2 - 5, display.height() / 2, display.width() / 2 + 5, display.height() / 2, SSD1306_WHITE);
  display.drawLine(display.width() / 2, display.height() / 2 - 5, display.width() / 2, display.height() / 2 + 5, SSD1306_WHITE);
  display.display();
  for (int i = 0; i < 120; i++) {
    odl= odleglosc()/3;
    //odl = 30;
    float ang=i*3*3.14159/180;
    display.drawPixel(int(display.width() / 2 + sin(ang)*odl), int(display.height() / 2 + cos(ang)*odl), SSD1306_WHITE);
    display.display();
    motor.angle(-3);
    //delay(500);
  }
}

void skan() {
  for (int i = 0; i < 360; i++) {
    data_skan[i][0] = i;
    data_skan[i][1] = odleglosc();
    motor.angle(1);
  }
}

long odleglosc() {
  long czas;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(2);
  digitalWrite(trigPin, LOW);

  //Pomiar wykonany
  czas = pulseIn(echoPin, HIGH);
  return czas / 58;
}
