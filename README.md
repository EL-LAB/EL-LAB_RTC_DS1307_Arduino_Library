# EL LAB: RTC DS1307 Arduino Library
This library allows configuring the RTC DS1307 to monitor time through the I2C interface.

There is additional information about the library and its uses in the following sections:
- [Arduino Examples](https://github.com/EL-LAB/EL-LAB_RTC_DS1307_Arduino_Library#arduino-examples)
- [Library Functions](https://github.com/EL-LAB/EL-LAB_RTC_DS1307_Arduino_Library#library-functions)
- [Date Formats](https://github.com/EL-LAB/EL-LAB_RTC_DS1307_Arduino_Library#date-formats)

## Arduino Examples
#### [RTC_Start](/examples/RTC_Start/RTC_Start.ino)
This example shows how to setup the RTC when it is not configured yet. Then it reads the data from the RTC and prints it in screen.
#### [RTC_Format](/examples/RTC_Format/RTC_Format.ino)
This example shows how the date and time from the RTC can be formatted to be shown in screen. It provides several examples of how the data can be shown depending on user needs.

## Library Functions
This library includes the following functions to initialize, write, read and erase data from the EEPROM memory 24LC256:
#### begin()
It starts the I2C communication on the board and checks if the RTC DS1307 is available. It doesn't require any argument and it returns `TRUE` if the memory is found or `FALSE` otherwise.
```C++
bool begin(void);
```
#### setDateTime()
It configures the date and time in the RTC DS1307. This function requires the year, month, day, hour, minute and second individually, or the date and time. This function doesn't return anything.
```C++
void setDateTime(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second);
void setDateTime(const char* date, const char* time);
```
#### getDateTime()
It gets the date and time from the RTC. The function doesn't require any argument. It returns the date and time.
```C++
DateTime getDateTime(void);
```
#### isReady()
It checks if the RTC is already configured and ready to work. 
```C++
uint8_t isReady(void);
```
#### dateFormat()
It allows to format the date and time provided by the RTC in several ways.
```C++
char* dateFormat(const char* dateFormat, DateTime dt);
```
## Date Formats
#### Day
- d : Day of the month in 2 digits with leading zeros (01 to 31)
- D : A textual representation of a day in three letters (Mon through Sun)
- j : Day of the month without leading zeros (1 to 31)
- l : A full textual representation of the day of the week (Sunday through Saturday)
- N : ISO-8601 numeric representation of the day of the week (1 for Monday through 7 for Sunday)
- S : English ordinal suffix for the day of the month in 2 characters (st, nd, rd or th. Works well with j)
- w : Numeric representation of the day of the week (0 for Sunday through 6 for Saturday)
- z : The day of the year (0 through 365)
#### Month
- F : A full textual representation of a month, such as January or March (January through December)
- m : Numeric representation of a month with leading zeros (01 through 12)
- M : A short textual representation of a month, three letters (Jan through Dec)
- n : Numeric representation of a month without leading zeros (1 through 12)
- t : Number of days in the given month (28 through 31)
#### Year
- L : Whether it's a leap year (1 if it is a leap year, 0 otherwise)
- Y : A full numeric representation of a year in 4 digits (Examples: 1999 or 2003)
- y : A two digit representation of a year (Examples: 99 or 03)
#### Time
- a : Lowercase Ante meridiem and Post meridiem (am or pm)
- A : Uppercase Ante meridiem and Post meridiem (AM or PM)
- g : 2-hour format of an hour without leading zeros (1 through 12)
- G : 24-hour format of an hour without leading zeros (0 through 23)
- h : 12-hour format of an hour with leading zeros (01 through 12)
- H : 24-hour format of an hour with leading zeros (00 through 23)
- i : Minutes with leading zeros (00 to 59)
- s : Seconds with leading zeros (00 through 59)
#### Dare formats (Full Date/Time)
- U : Seconds since the Unix Epoch (January 1 1970 00:00:00 GMT)
## Credits
This library is based on the code by jarzebski: https://github.com/jarzebski/Arduino-DS1307
