#include <Wire.h>
#include <DS3231.h>

#define SET_TIME 0 // Toggles whether the time needs to be calibrated

DS3231 clock; // RTC Module
RTCDateTime dt; // Date time object, struct with info about time

void setup() {
  Serial.begin(9600);
  clock.begin();
  if(SET_TIME) {
    while(Serial.available() == 0);

    int hour = Serial.parseInt();
    int minute = Serial.parseInt();
    int second = Serial.parseInt();
    //Set time 
    clock.setDateTime(2025, 11, 8, hour, minute, second);
  }
}

void loop() {
  dt = clock.getDateTime();

  Serial.print(dt.year); 
  Serial.print("-");
  Serial.print(dt.month); 
  Serial.print("-");
  Serial.print(dt.day); 
  Serial.print("-");
  Serial.print(dt.hour); 
  Serial.print(":");
  Serial.print(dt.minute); 
  Serial.print(":");
  Serial.print(dt.second); 
  Serial.println("");
  delay(1000);

}
