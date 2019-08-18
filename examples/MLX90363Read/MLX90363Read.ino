#include <SPI.h>
#include "melexis.h"

#define SS_PIN 10

MELEXIS test(SS_PIN);

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  delayMicroseconds(2500); //tSSRERE_mod3
  test.poll();

  Serial.print("X: ");
  Serial.print(test.get_x(), DEC);
  Serial.print(" Y: ");
  Serial.print(test.get_y(), DEC);
  Serial.print(" Z: ");
  Serial.println(test.get_z(), DEC);
}