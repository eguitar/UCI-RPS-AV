#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BMP3XX.h"

const int delay_time = 500;

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BMP3XX bmp;

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Adafruit BMP390");

  if (!bmp.begin_I2C()) {  // hardware I2C mode
    Serial.println("Could not find a valid BMP3xx sensor, check wiring!");
    while (1);
  }

  // Set up oversampling and filter initialization
  bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_2X);
  // BMP3_OVERSAMPLING_2X
  // BMP3_No_OVERSAMPLING
  bmp.setPressureOversampling(BMP3_OVERSAMPLING_32X);
  bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
  //DISABLE);
  //COEFF_3);
  bmp.setOutputDataRate(BMP3_ODR_25_HZ);

  Serial.println("Sekunden,Temp,Press,Alt");
}


void loop() {
  float Temp, Press, Alt;

  if (! bmp.performReading()) {
    Serial.println("Failed to perform reading.\n");
    exit(0);
  }

  Temp = bmp.temperature;
  Serial.print(Temp); Serial.print(",");
  
  Press = bmp.pressure / 100.0;
  Serial.print(Press); Serial.print(",");
  
  Alt = bmp.readAltitude(SEALEVELPRESSURE_HPA);
  Serial.println(Alt);

  delay(delay_time);
}
