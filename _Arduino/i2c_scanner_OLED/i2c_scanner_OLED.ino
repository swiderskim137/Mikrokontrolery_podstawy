#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);


void setup()
{
  Wire.begin();
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

    display.clearDisplay();

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);


}


void loop()
{
  byte error, address;
  int nDevices;

  display.clearDisplay();
  display.setCursor(0,0);
  
  display.println("Scanning...");

  nDevices = 0;
  for(address = 1; address < 127; address++ ) 
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      display.print("I2C device found at\naddress 0x");
      if (address<16) 
        display.print("0");
      display.print(address,HEX);
      display.println("  !");

      nDevices++;
    }
    else if (error==4) 
    {
      display.print("Unknow error at address 0x");
      if (address<16) 
        display.print("0");
      display.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    display.println("No I2C devices found\n");
  else
    display.println("done\n");

display.display();
  delay(5000);           // wait 5 seconds for next scan
}
