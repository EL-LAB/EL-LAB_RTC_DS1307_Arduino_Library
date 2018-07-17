/*
    RTC_Start.ino
    
    This example shows how to setup the RTC when it is
    not configured yet.
    
    Created: July 17th, 2018
    Author: El Lab de Electro: EL LAB
    Modified: -
    Author: -
    
    URL: https://github.com/EL-LAB/EL-LAB_RTC_DS1307_Arduino_Library
*/

#include <rtc.h>

RTC myRTC;
DateTime dt;

void setup()
{
  Serial.begin(9600);

  // Checking connection.
  if (myRTC.begin()) {
    Serial.println("RTC detected.");
  }
  else {
    Serial.println("RTC not detected!");
    return;
  }
  
  // Checks if RTC is already configured. If not, then configure it with sketch compiling time.
  if (!myRTC.isReady()) {
    myRTC.setDateTime(__DATE__, __TIME__);
    
    // RTC can be manual configured too (YYYY, MM, DD, HH, II, SS).
    // myRTC.setDateTime(2018, 7, 16, 12, 45, 00);
  }
}

void loop()
{
  // Gets date and time from RTC.
  dt = myRTC.getDateTime();

  // Prints date and time.
  Serial.print("\nDate: ");
  Serial.print(dt.year);   Serial.print("-");
  Serial.print(dt.month);  Serial.print("-");
  Serial.println(dt.day);
  Serial.print("Time: ");
  Serial.print(dt.hour);   Serial.print(":");
  Serial.print(dt.minute); Serial.print(":");
  Serial.println(dt.second);

  delay(5000); // Waits 5 seconds.
}
