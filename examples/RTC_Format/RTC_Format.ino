/*
    RTC_Format.ino
    
    This example shows how the date and time from the RTC
    can be formatted to be shown in screen.
    
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

  // Prints date and time in different formats.
  Serial.print("\nLong number format:          ");
  Serial.println(myRTC.dateFormat("d-m-Y H:i:s", dt));

  Serial.print("Long format with month name: ");
  Serial.println(myRTC.dateFormat("d F Y H:i:s",  dt));

  Serial.print("Short format with 12h mode: ");
  Serial.println(myRTC.dateFormat("jS M y, h:ia", dt));

  Serial.print("Today is:                    ");
  Serial.print(myRTC.dateFormat("l, z", dt));
  Serial.println(" days of the year.");

  Serial.print("Actual month has:            ");
  Serial.print(myRTC.dateFormat("t", dt));
  Serial.println(" days.");

  Serial.print("Unixtime:                    ");
  Serial.println(myRTC.dateFormat("U", dt));

  delay(5000); // Waits 5 seconds.
}
