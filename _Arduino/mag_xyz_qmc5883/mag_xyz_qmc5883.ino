/*
  ===============================================================================================================
  QMC5883LCompass.h Library XYZ Example Sketch
  Learn more at [https://github.com/mprograms/QMC5883Compas]

  This example shows how to get the XYZ values from the sensor.

  ===============================================================================================================
  Release under the GNU General Public License v3
  [https://www.gnu.org/licenses/gpl-3.0.en.html]
  ===============================================================================================================

  FROM QST QMC5883L Datasheet [https://nettigo.pl/attachments/440]
  -----------------------------------------------
  MODE CONTROL (MODE)
  Standby     0x00
  Continuous    0x01

  OUTPUT DATA RATE (ODR)
  10Hz          0x00
  50Hz          0x04
  100Hz         0x08
  200Hz         0x0C

  FULL SCALE (RNG)
  2G            0x00
  8G            0x10

  OVER SAMPLE RATIO (OSR)
  512           0x00
  256           0x40
  128           0x80
  64            0xC0

*/
#include <QMC5883LCompass.h>

QMC5883LCompass compass;

void setup() {
  Serial.begin(115200);
  compass.init();
  //void setMode(byte mode, byte odr, byte rng, byte osr);
  compass.setMode(0x01, 0x00, 0x00, 0x00);
}

float declinationAngle = (5.0 + (53.0 / 60.0)) / (180 / M_PI);//Zawada
float x = 0, y = 0, z = 0, sumx = 0, sumy = 0, srx = 0, sry = 0;
int samp = 10, n = 0;
void loop() {
  //n++;
  compass.read();
  // Read compass values
  // Return XYZ readings
  x = compass.getX();
  y = compass.getY();
  z = compass.getZ();
  /*for (int i = 1; i <= samp; i++) {
    compass.read();
    x += compass.getX();
    y += compass.getY();
    }
    x = x / samp;
    y = y / samp;
    sumx += x; srx = sumx / n;
    sumy += y; sry = sumy / n;
  */
  Serial.print("X: ");
  Serial.print(x);
  Serial.print(" Y: ");
  Serial.print(y);
  //Serial.print(" Xsr = ");
  //Serial.print(srx);
  //Serial.print(" Ysr = ");
  //Serial.print(sry);
  Serial.print(" Z: ");
  Serial.print(z);
  Serial.println();
  //x = 0; y = 0;
  delay(250);
}
