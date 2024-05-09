// UCI RP - SOLIDS - AVIONICS
#include <SD.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LIS3MDL.h>
#include "Adafruit_BMP3XX.h"
#include <Adafruit_LSM6DS3TRC.h>
#include <SoftwareSerial.h>
// ----------------------------
#define main_1 7     // main primary e-match
#define main_2 8     // main secondary e-match
#define drogue_1 9   // drogue primary e-match
#define drogue_2 10  // drogue secondary e-match
#define buzzer 6    // buzzer
#define SEALEVELPRESSURE_HPA (1013.25)
// ----------------------------
Adafruit_BMP3XX bmp;
Adafruit_LIS3MDL mdl;
Adafruit_LSM6DS3TRC lsm;
SoftwareSerial mySerial(0,1); // RX, TX
// ----------------------------
const int delay_time = 500;
const int charge_delay = 500;
const int backup_delay = 2500;
bool launch_flag;
bool drogue_flag;
bool main_flag;
bool lis3mdl;
bool lis3dh;
int fall_counter;
float pre_alt;

// #######################################################################
// #######################################################################

void writeSD(String data) {
  File dataFile = SD.open("data_log.csv", FILE_WRITE);  
  if (dataFile) {
    dataFile.println(data);
    dataFile.close();
  }
  else {
    Serial.println("Error Opening Data File.\n");
  }
}

void setup() {

  // Serial.print("FLIGHT COMPUTER ON\n");
  tone(buzzer, 3000, 1000);
  Serial.begin(115200);
  mySerial.begin(57600);

  // Serial.print("Initializing SD card...");
  if (!SD.begin(BUILTIN_SDCARD)) {
    // Serial.print("card failed, or not present.\n");
    exit(0);
  }
  // Serial.print("SD-CARD initialized.\n");

  // Serial.print("Connecting to BMP3XX...");
  if (!bmp.begin_I2C(0x77, &Wire2)) {
    // Serial.print("sensor not found, check wiring!\n");
    writeSD("BMP3XX not found");
    exit(0);
  }
  // Serial.print("BMP3XX found.\n");

  // Serial.print("Connecting to LSM6DS3TR-C...");
  if (!lsm.begin_I2C(0x6A, &Wire2)) {
    // Serial.print("sensor not found, check wiring!\n");
    writeSD("LSM6DS3TR-C not found");
    exit(0);
  }
  // Serial.print("LSM6DS3TR-C found.\n");

  lis3mdl = true;
  // Serial.print("Connecting to LIS3MDL...");
  if (!mdl.begin_I2C(0x1C, &Wire2)) {
    Serial.print("sensor not found, check wiring!\n");
    lis3mdl = false;
    writeSD("LIS3MDL not found");
    // exit(0);
  }
  // Serial.print("LIS3MDL found.\n");
  
  Serial.print("Altitude, Temperature, Pressure, Acceleration [X, Y, Z] (m/s^2), Orientation [X, Y, Z] (rad/s), Magnetic Field [X, Y, Z] (uTesla):\n");

  launch_flag = true;
  drogue_flag = false;
  main_flag = false;
  fall_counter = 0;
  pre_alt = 0;

  digitalWrite(drogue_1, HIGH);
  delay(charge_delay);
  digitalWrite(drogue_1, LOW);
  delay(backup_delay);
  digitalWrite(drogue_2, HIGH);
  delay(charge_delay);
  digitalWrite(drogue_2, LOW);

  digitalWrite(main_1, HIGH);
  delay(charge_delay);
  digitalWrite(main_1, LOW);
  delay(backup_delay);
  digitalWrite(main_2, HIGH);
  delay(charge_delay);
  digitalWrite(main_2, LOW);

  delay(2000);
  tone(buzzer, 3000, 1000);
}

// #######################################################################
// #######################################################################

float alt, temp, pres;
float acc_x, acc_y, acc_z;
float gyro_x, gyro_y, gyro_z;
float mag_x, mag_y, mag_z;

void loop() {
  // tone(buzzer, 2000, 500); // comment out for actual flight
  
  if (! bmp.performReading()) {
    // Serial.println("BMP failed to perform reading.\n");
    writeSD("BMP3XX Sensor Failure");
    exit(0);
  }
  
  alt = bmp.readAltitude(SEALEVELPRESSURE_HPA);
  temp = bmp.temperature;
  pres = bmp.pressure / 100.0;

  sensors_event_t acc, gyro, tmp; 
  lsm.getEvent(&acc, &gyro, &tmp);

  acc_x = acc.acceleration.x;
  acc_y = acc.acceleration.y;
  acc_z = acc.acceleration.z;

  gyro_x = gyro.gyro.x;
  gyro_y = gyro.gyro.y;
  gyro_z = gyro.gyro.z;

  if (lis3mdl) {
    sensors_event_t mag;
    mdl.getEvent(&mag);
    mag_x = mag.magnetic.x;
    mag_y = mag.magnetic.y;
    mag_z = mag.magnetic.z;
  }
  else {
    mag_x = 0.0;
    mag_y = 0.0;
    mag_z = 0.0;
  }
  
  // {tasks} ------------------------------------
  if (launch_flag == false) {

    if (abs(acc_x) > 30) {      // launch condition for rocket - acceleration spikes
      launch_flag = true;
      // Serial.println("ROCKET LAUNCH++++++++++++++++++++");
    }
    else if (abs(acc_y) > 30) { // launch condition for rocket - acceleration spikes
      launch_flag = true;
      // Serial.println("ROCKET LAUNCH++++++++++++++++++++");
    }
    else if (abs(acc_z) > 30) { // launch condition for rocket - acceleration spikes
      launch_flag = true;
      // Serial.println("ROCKET LAUNCH++++++++++++++++++++");
    }
    else {
      // Serial.println("NO LAUNCH--------------------");
    }
  }
  else if (launch_flag == true && drogue_flag == false) {
    
    if (fall_counter > 3 && pre_alt - alt > 0) {
      drogue_flag = true;
      digitalWrite(drogue_1, HIGH);
      delay(charge_delay);
      digitalWrite(drogue_1, LOW);
      // Serial.println("DROGUE 1 FIRE++++++++++++++++++++");
      delay(backup_delay);
      digitalWrite(drogue_2, HIGH);
      delay(charge_delay);
      digitalWrite(drogue_2, LOW);
      // Serial.println("DROGUE 2 FIRE++++++++++++++++++++");
      tone(buzzer, 3000, 1000);
      writeSD("DROGUE EJECTED");
    }
    else if (pre_alt - alt > 0) {
      fall_counter = fall_counter + 1;
      // Serial.println("FALLING--------------------");
    }
    else {
      fall_counter = 0;
      // Serial.println("NO FALL--------------------");
    }

  }
  else if (launch_flag == true && main_flag == false) {
    
    if (alt < 1500) { // eject condition for main - 1,750 ft alt
      main_flag = true;
      digitalWrite(main_1, HIGH);
      delay(charge_delay);
      digitalWrite(main_1, LOW);
      // Serial.println("MAIN 1 FIRE++++++++++++++++++++");
      delay(backup_delay);
      digitalWrite(main_2, HIGH);
      delay(charge_delay);
      digitalWrite(main_2, LOW);
      // Serial.println("MAIN 2 FIRE++++++++++++++++++++");
      tone(buzzer, 3000, 1000);
      writeSD("MAIN EJECTED");
    }
    else {
      // Serial.println("FALLING--------------------");
    }
  }
  pre_alt = alt;

  // {datalogging} ------------------------------------
  String dataString = String(alt) + "," + 
                      String(temp) + "," + 
                      String(pres) + "," +
                      String(acc_x) + "," +
                      String(acc_y) + "," +
                      String(acc_z) + "," +
                      String(gyro_x) + "," +
                      String(gyro_y) + "," +
                      String(gyro_z) + "," +
                      String(mag_x) + "," +
                      String(mag_y) + "," +
                      String(mag_z);
                      
  Serial.println(dataString);
  mySerial.println(dataString);
  
  File dataFile = SD.open("data_log.csv", FILE_WRITE);
  
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
  }
  else {
    Serial.println("Error Opening Data File.\n");
  }
  // --------------------------------------------------
  delay(delay_time);
}

// #######################################################################
