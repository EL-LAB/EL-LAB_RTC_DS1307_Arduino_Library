/***********************************************************************
* FILENAME: rtc.h
*
* DESCRIPTION:
*       Arduino library for the Real Time Clock (RTC) DS1307. 
*
*CREDITS:
*       This library is based on the code by jarzebski: 
*           https://github.com/jarzebski/Arduino-DS1307
*
* URL:  https://github.com/EL-LAB/EL-LAB_RTC_DS1307_Arduino_Library
* 
* AUTHOR:  Diego Villalobos    START DATE :  July 17 2018
*
* CHANGES:
*
* VERSION      DATE         WHO         DETAIL
*  1.0.0   July 17 2018   Diego V.      Initial release
*
***********************************************************************/

#ifndef _RTC_H_
#define _RTC_H_

#ifdef ARDUINO
    #if ARDUINO < 100
        #include "WProgram.h"
    #else
        #include "Arduino.h"
    #endif
#endif // ARDUINO

#include <Wire.h>

#define RTC_REG_TIME    0x00

struct DateTime { 
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    uint8_t dayOfWeek;
    uint32_t unixtime;
}; // DateTime struct

class RTC {
    public:
        RTC(uint8_t address);

        bool begin(void);

        void setDateTime(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second);
        void setDateTime(const char* date, const char* time);
        DateTime getDateTime(void);
        uint8_t isReady(void);

        char* dateFormat(const char* dateFormat, DateTime dt);

    private:
        DateTime t;
        uint8_t _devAddress;

        char *strDayOfWeek(uint8_t dayOfWeek);
        char *strMonth(uint8_t month);
        char *strAmPm(uint8_t hour, bool uppercase);
        char *strDaySufix(uint8_t day);

        uint8_t hour12(uint8_t hour24);
        uint8_t bcd2dec(uint8_t bcd);
        uint8_t dec2bcd(uint8_t dec);

        long time2long(uint16_t days, uint8_t hours, uint8_t minutes, uint8_t seconds);
        uint16_t date2days(uint16_t year, uint8_t month, uint8_t day);
        uint8_t daysInMonth(uint16_t year, uint8_t month);
        uint16_t dayInYear(uint16_t year, uint8_t month, uint8_t day);
        bool isLeapYear(uint16_t year);
        uint8_t dow(uint16_t y, uint8_t m, uint8_t d);

        uint32_t unixtime(void);
        uint8_t conv2d(const char* p);
};

#endif // _RTC_H_
