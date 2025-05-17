/*
   AD5242 Digital Pot Test

    Uses Arduino Uno


   Library used:  AD524x by Rob Tillaart
                
   Tested with Arduino IDE 2.3.4
               AD524x 0.5.1
               

   Gadget Reboot
   https://www.youtube.com/@gadgetreboot
*/

#include "AD524X.h"
AD524X AD01(0x2C);  //  address pins AD0 & AD1 = GND

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AD524X_LIB_VERSION: ");
  Serial.println(AD524X_LIB_VERSION);

  Wire.begin();
  Wire.setClock(400000);

  i2c_scanner();  // check for I2C device address if needed

  bool b = AD01.begin();
  Serial.println(b ? "true" : "false");
  Serial.println(AD01.isConnected());
}

void loop() {

  // move pot wiper between min/max/mid points
  Serial.println(255);
  AD01.write(1, 255);
  delay(5000);

  Serial.println("midScaleReset(1)");
  AD01.midScaleReset(1);
  delay(5000);

  Serial.println(0);
  AD01.write(1, 0);
  delay(5000);

  // increment pot wiper from end to end
  for (int val = 0; val <= 255; val++) {
    AD01.write(1, val);
    Serial.println(val);
    delay(50);
  }
}

void i2c_scanner() {
  byte error, address;
  int nDevices;
  Serial.println("Scanning...");
  nDevices = 0;
  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
      nDevices++;
    } else if (error == 4) {
      Serial.print("Unknow error at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0) {
    Serial.println("No I2C devices found\n");
  } else {
    Serial.println("done\n");
  }
  delay(500);
}
