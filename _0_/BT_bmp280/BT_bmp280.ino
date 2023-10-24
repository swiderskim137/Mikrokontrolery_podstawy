#include <Wire.h>
#include <SPI.h>                                       //dodaj bibliotekę SPI.h
#include <SD.h>                                          //dodaj bilbiotekę SD.h
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#define SEALEVELPRESSURE_HPA (1013.25)
unsigned long delayTime = 1000;
float h0;
float T, H, P;
Adafruit_BME280 bme; // I2C

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);

  if (! bme.begin(0x76, &Wire)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    digitalWrite(LED_BUILTIN, HIGH);
    while (1);
  }
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("BME280 OK");
  h0 = bme.readAltitude(SEALEVELPRESSURE_HPA);
}

void loop() {
  bme.takeForcedMeasurement();
  T = bme.readTemperature();
  P = bme.readPressure() / 100.0F;
  H = bme.readHumidity();

  //Send data over Bluetooth
  Serial.print("*T" + String(T) + "*");
  Serial.print("*P" + String(P) + "*");
  Serial.print("*H" + String(H) + "*");

  printValues();
  delay(delayTime);
}

void printValues() {
  Serial.print("t = ");
  Serial.print(millis() / 1000);
  Serial.println(" s");

  Serial.print("Temperature = ");
  Serial.print(bme.readTemperature());
  Serial.println(" *C");

  Serial.print("Pressure = ");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.println(" hPa");

  Serial.print("Approx. Altitude = ");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA) - h0);
  Serial.println(" m");

  Serial.print("Humidity = ");
  Serial.print(bme.readHumidity());
  Serial.println(" %");

  Serial.println();
}
