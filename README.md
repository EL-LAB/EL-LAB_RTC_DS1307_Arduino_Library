# EL LAB: RTC DS1307 Arduino Library
This library allows configuring the RTC DS1307 to monitor time through the I2C interface.

There is additional information about the library and its uses in the following sections:
- [Arduino Examples](https://github.com/EL-LAB/EL-LAB_EEPROM_24LC256_Arduino_Library#arduino-examples)
- [Library Functions](https://github.com/EL-LAB/EL-LAB_EEPROM_24LC256_Arduino_Library#library-functions)

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

