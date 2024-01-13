// UCI RP - SOLIDS - AVIONICS

#include <SD.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LIS3MDL.h>
#include "Adafruit_BMP3XX.h"
#include <Adafruit_LSM6DS3TRC.h>
#define SEALEVELPRESSURE_HPA (1017)
// ----------------------------
#define main_1 7     // main primary
#define main_2 8     // main secondary     
#define drogue_1 9   // drogue primary
#define drogue_2 10  // drogue secondary
// #define buzzer 28    // buzzer
// ----------------------------
Adafruit_BMP3XX bmp;
Adafruit_LIS3MDL mdl;
Adafruit_LSM6DS3TRC lsm;
// ----------------------------
const int delay_time = 1000;
const int charge_delay = 500;
const int backup_delay = 2500;
bool launch_flag;
bool drogue_flag;
bool main_flag;
int fall_counter;
float pre_alt;

// #######################################################################
// #######################################################################

void setup() {

  Serial.begin(9600);

  delay(2000);

  // Serial.print("FLIGHT COMPUTER ON\n");
  // tone(buzzer, 440, 1000);

  Serial.print("Initializing SD card...");
  if (!SD.begin(BUILTIN_SDCARD)) {
    Serial.print("card failed, or not present.\n");
    Serial.print("### -- Flight Computer Crashed. -- ###\n");
    exit(0);
  }
  Serial.print("card initialized.\n");

  // Serial.print("Connecting to BMP3XX...");
  // if (!bmp.begin_I2C()) {
  //   Serial.print("sensor not found, check wiring!\n");
  //   Serial.print("### -- Flight Computer Crashed. -- ###\n");
  //   exit(0);
  // }
  // Serial.print("sensor found.\n");

  // Serial.print("Connecting to LSM6DS3TR-C...");
  // if (!lsm.begin_I2C()) {
  //   Serial.print("sensor not found, check wiring!\n");
  //   Serial.print("### -- Flight Computer Crashed. -- ###\n");
  //   exit(0);
  // }
  // Serial.print("sensor found.\n");

  Serial.print("Connecting to LIS3MDL...");
  if (!mdl.begin_I2C()) {
    Serial.print("sensor not found, check wiring!\n");
    Serial.print("### -- Flight Computer Crashed. -- ###\n");
    exit(0);
  }
  Serial.print("sensor found.\n");

  Serial.print("Altitude, Temperature, Pressure, Acceleration [X, Y, Z] (m/s^2), Orientation [X, Y, Z] (rad/s), Magnetic Field [X, Y, Z] (uTesla):\n");

  launch_flag = false;
  drogue_flag = false;
  main_flag = false;
  fall_counter = 0;
  pre_alt = 0;

  // digitalWrite(drogue_1, HIGH);
  // delay(charge_delay);
  // digitalWrite(drogue_1, LOW);
  // Serial.println("DROGUE 1 FIRE++++++++++++++++++++");
  // delay(backup_delay);
  // digitalWrite(drogue_2, HIGH);
  // delay(charge_delay);
  // digitalWrite(drogue_2, LOW);
  // Serial.println("DROGUE 2 FIRE++++++++++++++++++++");

  // digitalWrite(main_1, HIGH);
  // delay(charge_delay);
  // digitalWrite(main_1, LOW);
  // Serial.println("MAIN 1 FIRE++++++++++++++++++++");
  // delay(backup_delay);
  // digitalWrite(main_2, HIGH);
  // delay(charge_delay);
  // digitalWrite(main_2, LOW);
  // Serial.println("MAIN 2 FIRE++++++++++++++++++++");

}

// #######################################################################
// #######################################################################

float alt, temp, pres;
float acc_x, acc_y, acc_z;
float gyro_x, gyro_y, gyro_z;
float mag_x, mag_y, mag_z;

void loop() {
  
  
  // --------------------------------------------------
  delay(delay_time);
}

// #######################################################################
