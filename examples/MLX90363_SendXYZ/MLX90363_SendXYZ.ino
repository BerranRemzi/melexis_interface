#include <SPI.h>
#include "melexis.h"

#define FILTER 16

// constants won't change. Used here to set a pin number:
const int ledPin =  LED_BUILTIN;// the number of the LED pin

// Variables will change:
int ledState = LOW;             // ledState used to set the LED

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change:
const long interval = 100;           // interval at which to blink (milliseconds)


MELEXIS test(10);

long xAverage, yAverage, zAverage;
float x, y, z;

void setup() {
  // set the digital pin as output:
  pinMode(ledPin, OUTPUT);
  Serial.begin(112500);
}

void loop() {
  delayMicroseconds(2500); //tSSRERE_mod3
  test.poll();
  if (test.get_x() != 0) {
    x = Average(&xAverage, test.get_x(), FILTER) * 0.02197 * 4;
    y = Average(&yAverage, test.get_y(), FILTER) * 0.02197 * 4;
    z = Average(&zAverage, test.get_z(), FILTER) * 0.02197 * 4;
  }

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    SendData();
  }
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