/*
  ===============================================================================================================
  QMC5883LCompass.h Library XYZ Example Sketch
  Learn more at [https://github.com/mprograms/QMC5883Compas]

  This example shows how to get the XYZ values from the sensor.

  ===============================================================================================================
  Release under the GNU General Public License v3
  [https://www.gnu.org/licenses/gpl-3.0.en.html]
  ===============================================================================================================
*/
#include <QMC5883LCompass.h>
#include <Stepmot.h>
QMC5883LCompass compass;
Stepmot motor;

void setup() {
  Serial.begin(9600);
  compass.init();
  motor.init(4096, 2, 3, 4, 5);
  motor.angle(90);
}
int x, y, z;
void loop() {
  compass.read();
  y = compass.getY();
  Serial.print(" Y: ");
  Serial.println(y);
  Serial.println(motor.num_step);
  Serial.println(motor.num_stepf, 8);
  Serial.println(motor.tot_step);
  Serial.println(motor.tot_stepf);
  Serial.println(motor.tot_stepf, 8);
  if (y > 20) {
    motor.angle(1);
  }
  if (y < -20) {
    motor.angle(-1);
  }
  //delay(100);
}
