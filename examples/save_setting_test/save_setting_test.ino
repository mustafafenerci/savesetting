/**
 * @file       save_setting_test.ino
 * @author     Mustafa Fenerci	mustafafenercieem@gmail.com
 * @date       Sep 2020
 * @breif	   for ESP32 and ESP8266 Save Setting
 */

#define _FirstMaxDataSize 12
#define _SecondMaxDataSize 10

#include <SaveSetting.h>

SaveSetting example1(_FirstMaxDataSize); // class definition
SaveSetting example2(_SecondMaxDataSize);

void setup() {
  Serial.begin(115200);  
  while(!Serial);
  delay(2000);
  Serial.println("\nSaveSetting Start...");
  savesetting.begin();
  Serial.println("Use Memory: " + String(Memory.totalLength()));

  
  example1.write("Hello");
  Serial.println(example1.length());      // size of data currently used
 
  example2.write("World");			      // write data
  Serial.println(example2.length());      
  
  Serial.println(example1.read() + " " + example2.read()); // read data
  example2.clear();
  Serial.println(example1.read() + " " + example2.read()); // read data
  
}

void loop() {
   

}