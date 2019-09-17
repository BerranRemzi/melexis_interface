#include <xOS.h>

#include <SPI.h>
#include "melexis.h"

#define FILTER 16
#define LED 7

Task_t TaskStruct[4];
MELEXIS test(10);

long xAverage, yAverage, zAverage;
float x, y, z;
void setup()
{
  Serial.begin(112500);
  pinMode(LED, OUTPUT);
  
  xInit(TaskStruct);      //Struct with function parameters
  xTaskCreate(  &SendData,    100,     0,        0);
}

void loop()
{
  delayMicroseconds(2500); //tSSRERE_mod3
  test.poll();
  //Serial.println("No Response");
  if (test.get_x() != 0) {

    x = Average(&xAverage, test.get_x(), FILTER) * 0.02197 * 4;
    y = Average(&yAverage, test.get_y(), FILTER) * 0.02197 * 4;
    z = Average(&zAverage, test.get_z(), FILTER) * 0.02197 * 4;


    if (z > 30) {
      digitalWrite(LED, HIGH);
    } else if (z < -30) {
      digitalWrite(LED, LOW);
    }
  }

  xLoop();  //xOS task
}

int Average(long *adc_average, int _new_sample, int filter_factor_level)
{
  *adc_average -= *adc_average / filter_factor_level;
  *adc_average += _new_sample;
  return *adc_average / filter_factor_level;
}

void SendData(void) {
  Serial.print(x, 2);
  Serial.print(",");
  Serial.print(y, 2);
  Serial.print(",");
  Serial.println(z, 2);
}
