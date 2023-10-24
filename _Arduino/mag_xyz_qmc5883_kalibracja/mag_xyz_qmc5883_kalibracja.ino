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
#include <Stepmot.h>

Stepmot motor;

QMC5883LCompass compass;
//float declinationAngle = (5.0 + (53.0 / 60.0)) / (180 / M_PI);//Zawada
float declinationAngle = (5.0 + (53.0 / 60.0));//Zawada
float x = 0, y = 0, z = 0, sumx = 0, sumy = 0, srx = 0, sry = 0;
float xdat[2][2] = {-10000, 0, 10000, 0};
int samp = 10, n = 0;
void setup() {
  Serial.begin(115200);
  motor.init(4096, 2, 3, 4, 5);
  compass.init();
  //void setMode(byte mode, byte odr, byte rng, byte osr);
  compass.setMode(0x01, 0x00, 0x00, 0x00);
  motor.setSpeed(30);
  //motor.angle(-90);
  for (int i = 0; i < 360; i++) {
    //n++;
    Serial.println(i * 10);
    compass.read();
    // Read compass values
    // Return XYZ readings
    //x = compass.getX();
    //y = compass.getY();
    //z = compass.getZ();
    for (int i = 1; i <= samp; i++) {
      compass.read();
      x += compass.getX();
      y += compass.getY();
      z += compass.getZ();
    }
    x = x / samp;
    y = y / samp;
    z = z / samp;
    //sumx += x; srx = sumx / n;
    //sumy += y; sry = sumy / n;
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
    if (x>xdat[0][0]){
      xdat[0][0]=x;
      xdat[0][1]=i;
    }
    if (x<xdat[1][0]){ 
      xdat[1][0]=x;
      xdat[1][1]=i;
    }
    x = 0; y = 0; z = 0;
    //delay(250);
    
    motor.angle(1);
  }
  Serial.println();
  Serial.println();
  Serial.print(xdat[0][0]);
  Serial.print(" ");
  Serial.println(xdat[0][1]);
  Serial.print(xdat[1][0]);
  Serial.print(" ");
  Serial.println(xdat[1][1]);
  Serial.println(declinationAngle);
  delay(250);
  motor.setSpeed(1);
  motor.angle(-360);
  //motor.angle(-360);
  //motor.angle(abs(xdat[0][1]-xdat[1][1])/2+xdat[0][1]-declinationAngle);
  delay(250);
  //motor.angle(-declinationAngle);
}


void loop() {

}
