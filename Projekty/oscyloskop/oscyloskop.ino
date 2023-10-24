#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     4
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int datv[128], V;
int poz = 0;
float vpp = 60 / 5; //volty na piksel
int xt = 0;
int odczytanaWartosc = 0;//Odczytana wartość z ADC
float napiecie = 0;//Wartość przeliczona na napięcie w V
int n = 127;

void setup() {
  Serial.begin(9600);
  //oled seting---------
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(2, 2);
  display.clearDisplay();
  //---------------------
  okno();
  long int ts = millis();
  for (int i = 0; i < n; i++) {
    napiecie = analogRead(A5) * (5.0 / 1024.0);
    display.fillRect(1, 1, 30, 8, SSD1306_BLACK);
    display.setCursor(2, 2);
    display.print(napiecie);
    display.drawPixel(poz, 62 - napiecie * vpp, SSD1306_WHITE);
    display.display();
    poz = (poz + 1) % 127;
    if (poz == 0) {
      display.clearDisplay();
      //okno();
    }
  }
  long int tt = millis() - ts;
  Serial.print("tt = ");
  Serial.println(tt);
  Serial.print("dt = ");
  Serial.print(tt / n);
  Serial.println(" ms");
  xt = tt / n * 20;

  okno();
}
float v2 = 0;
void loop() {
  //odczytanaWartosc = analogRead(A5);
  napiecie = analogRead(A5) * (5.0 / 1024.0);
  display.fillRect(1, 1, 30, 8, SSD1306_BLACK);
  display.setCursor(2, 2);
  display.print(napiecie);
  display.drawPixel(poz, 62 - napiecie * vpp, SSD1306_WHITE);
  display.display();
  poz = (poz + 1) % 127;
  if (poz == 0) {
    display.clearDisplay();
    okno();
  }
}

void okno() {
  display.drawRect(0, 0, display.width(), display.height(), SSD1306_WHITE);
  for (int i = 0; i < 6; i++) {
    display.drawLine(0, vpp * i + 2, 5, vpp * i + 2, SSD1306_WHITE);
    display.drawLine(display.width() - 5, vpp * i + 2, display.width(), vpp * i + 2, SSD1306_WHITE);
    for (int j = 0; j < display.width(); j = j + 20) {
      display.drawPixel(j, vpp * i + 2, SSD1306_WHITE);
    }
  }
  display.setCursor(2, 54);
  display.print(xt);
  display.display();
}
