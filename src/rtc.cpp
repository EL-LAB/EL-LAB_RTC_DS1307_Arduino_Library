/***********************************************************************
* FILENAME: rtc.cpp
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

#include "rtc.h"

const uint8_t daysArray [] PROGMEM = { 31,28,31,30,31,30,31,31,30,31,30,31 };
const uint8_t dowArray[] PROGMEM = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };

RTC::RTC(void) {

}

bool RTC::begin(void) {
    Wire.begin();

    // DateTime struct
    // By default (dummy values) January 1st, 2000 0h 0m 0s Saturday
    t.year = 2000;
    t.month = 1;
    t.day = 1;
    t.hour = 0;
    t.minute = 0;
    t.second = 0;
    t.dayOfWeek = 6;
    t.unixtime = 946681200;

    Wire.beginTransmission(RTC_ADDRESS);
    return (Wire.endTransmission() == 0);
}

void RTC::setDateTime(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second) {
    Wire.beginTransmission(RTC_ADDRESS);
    Wire.write(RTC_REG_TIME);
    Wire.write(dec2bcd(second));
    Wire.write(dec2bcd(minute));
    Wire.write(dec2bcd(hour));
    Wire.write(dec2bcd(dow(year, month, day)));
    Wire.write(dec2bcd(day));
    Wire.write(dec2bcd(month));
    Wire.write(dec2bcd(year-2000));
    Wire.write(RTC_REG_TIME);
    Wire.endTransmission();
}

void RTC::setDateTime(const char* date, const char* time) {
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;

    year = conv2d(date + 9);

    switch (date[0]){
        case 'J': month = date[1] == 'a' ? 1 : month = date[2] == 'n' ? 6 : 7; break;
        case 'F': month = 2; break;
        case 'A': month = date[2] == 'r' ? 4 : 8; break;
        case 'M': month = date[2] == 'r' ? 3 : 5; break;
        case 'S': month = 9; break;
        case 'O': month = 10; break;
        case 'N': month = 11; break;
        case 'D': month = 12; break;
    }

    day = conv2d(date + 4);
    hour = conv2d(time);
    minute = conv2d(time + 3);
    second = conv2d(time + 6);

    setDateTime(year+2000, month, day, hour, minute, second);
}

char* RTC::dateFormat(const char* dateFormat, DateTime dt) {
    char static buffer[255];

    buffer[0] = 0;

    char helper[11];

    while (*dateFormat != '\0') {
        switch (dateFormat[0]) {
            // Day decoder
            case 'd':
                sprintf(helper, "%02d", dt.day); 
                strcat(buffer, (const char *)helper); 
                break;
            case 'j':
                sprintf(helper, "%d", dt.day);
                strcat(buffer, (const char *)helper);
                break;
            case 'l':
                strcat(buffer, (const char *)strDayOfWeek(dt.dayOfWeek));
                break;
            case 'D':
                strncat(buffer, strDayOfWeek(dt.dayOfWeek), 3);
                break;
            case 'N':
                sprintf(helper, "%d", dt.dayOfWeek);
                strcat(buffer, (const char *)helper);
                break;
            case 'w':
                sprintf(helper, "%d", (dt.dayOfWeek + 7) % 7);
                strcat(buffer, (const char *)helper);
                break;
            case 'z':
                sprintf(helper, "%d", dayInYear(dt.year, dt.month, dt.day));
                strcat(buffer, (const char *)helper);
                break;
            case 'S':
                strcat(buffer, (const char *)strDaySufix(dt.day));
                break;

            // Month decoder
            case 'm':
                sprintf(helper, "%02d", dt.month);
                strcat(buffer, (const char *)helper);
                break;
            case 'n':
                sprintf(helper, "%d", dt.month);
                strcat(buffer, (const char *)helper);
                break;
            case 'F':
                strcat(buffer, (const char *)strMonth(dt.month));
                break;
            case 'M':
                strncat(buffer, (const char *)strMonth(dt.month), 3);
                break;
            case 't':
                sprintf(helper, "%d", daysInMonth(dt.year, dt.month));
                strcat(buffer, (const char *)helper);
                break;

            // Year decoder
            case 'Y':
                sprintf(helper, "%d", dt.year); 
                strcat(buffer, (const char *)helper); 
                break;
            case 'y': sprintf(helper, "%02d", dt.year-2000);
                strcat(buffer, (const char *)helper);
                break;
            case 'L':
                sprintf(helper, "%d", isLeapYear(dt.year)); 
                strcat(buffer, (const char *)helper); 
                break;

            // Hour decoder
            case 'H':
                sprintf(helper, "%02d", dt.hour);
                strcat(buffer, (const char *)helper);
                break;
            case 'G':
                sprintf(helper, "%d", dt.hour);
                strcat(buffer, (const char *)helper);
                break;
            case 'h':
                sprintf(helper, "%02d", hour12(dt.hour));
                strcat(buffer, (const char *)helper);
                break;
            case 'g':
                sprintf(helper, "%d", hour12(dt.hour));
                strcat(buffer, (const char *)helper);
                break;
            case 'A':
                strcat(buffer, (const char *)strAmPm(dt.hour, true));
                break;
            case 'a':
                strcat(buffer, (const char *)strAmPm(dt.hour, false));
                break;

            // Minute decoder
            case 'i': 
                sprintf(helper, "%02d", dt.minute);
                strcat(buffer, (const char *)helper);
                break;

            // Second decoder
            case 's':
                sprintf(helper, "%02d", dt.second); 
                strcat(buffer, (const char *)helper); 
                break;

            // Misc decoder
            case 'U': 
                sprintf(helper, "%lu", dt.unixtime);
                strcat(buffer, (const char *)helper);
                break;

            default: 
                strncat(buffer, dateFormat, 1);
                break;
        }
        dateFormat++;
    }

    return buffer;
}

DateTime RTC::getDateTime(void) {
    int values[7];

    Wire.beginTransmission(RTC_ADDRESS);
    Wire.write(RTC_REG_TIME);
    Wire.endTransmission();

    Wire.requestFrom(RTC_ADDRESS, 7);

    while(!Wire.available()) {};

    for (int i = 6; i >= 0; i--) {
        if (i == 3) {
            values[i] = Wire.read();
        }
        else {
            values[i] = bcd2dec(Wire.read());
        }
    }

    Wire.endTransmission();

    t.year = values[0] + 2000;
    t.month = values[1];
    t.day = values[2];
    t.dayOfWeek = values[3];
    t.hour = values[4];
    t.minute = values[5];
    t.second = values[6];
    t.unixtime = unixtime();

    return t;
}

uint8_t RTC::isReady(void)  {
    Wire.beginTransmission(RTC_ADDRESS);

    Wire.write(RTC_REG_TIME);
    Wire.endTransmission();
    Wire.requestFrom(RTC_ADDRESS, 1);

    while(!Wire.available()) {};

    uint8_t ss = Wire.read();

    Wire.endTransmission();

    return !(ss>>7);
}

uint8_t RTC::bcd2dec(uint8_t bcd) {
    return ((bcd / 16) * 10) + (bcd % 16);
}

uint8_t RTC::dec2bcd(uint8_t dec) {
    return ((dec / 10) * 16) + (dec % 10);
}

char *RTC::strDayOfWeek(uint8_t dayOfWeek) {
    switch (dayOfWeek) {
        case 1:
            return "Monday";
            break;
        case 2:
            return "Tuesday";
            break;
        case 3:
            return "Wednesday";
            break;
        case 4:
            return "Thursday";
            break;
        case 5:
            return "Friday";
            break;
        case 6:
            return "Saturday";
            break;
        case 7:
            return "Sunday";
            break;
        default:
            return "Unknown";
    }
}

char *RTC::strMonth(uint8_t month) {
    switch (month) {
        case 1:
            return "January";
            break;
        case 2:
            return "February";
            break;
        case 3:
            return "March";
            break;
        case 4:
            return "April";
            break;
        case 5:
            return "May";
            break;
        case 6:
            return "June";
            break;
        case 7:
            return "July";
            break;
        case 8:
            return "August";
            break;
        case 9:
            return "September";
            break;
        case 10:
            return "October";
            break;
        case 11:
            return "November";
            break;
        case 12:
            return "December";
            break;
        default:
            return "Unknown";
    }
}

char *RTC::strAmPm(uint8_t hour, bool uppercase) {
    if (hour < 12) {
        if (uppercase) {
            return "AM";
        }
        else {
            return "am";
        }
    }
    else {
        if (uppercase) {
            return "PM";
        }
        else {
            return "pm";
        }
    }
}

char *RTC::strDaySufix(uint8_t day) {
    if (day % 10 == 1) {
        return "st";
    }
    if (day % 10 == 2) {
        return "nd";
    }
    if (day % 10 == 3) {
        return "rd";
    }

    return "th";
}

uint8_t RTC::hour12(uint8_t hour24) {
    if (hour24 == 0) {
        return 12;
    }

    if (hour24 > 12) {
       return (hour24 - 12);
    }

    return hour24;
}

long RTC::time2long(uint16_t days, uint8_t hours, uint8_t minutes, uint8_t seconds) {
    return ((days * 24L + hours) * 60 + minutes) * 60 + seconds;
}

uint16_t RTC::dayInYear(uint16_t year, uint8_t month, uint8_t day) {
    uint16_t fromDate;
    uint16_t toDate;

    fromDate = date2days(year, 1, 1);
    toDate = date2days(year, month, day);

    return (toDate - fromDate);
}

bool RTC::isLeapYear(uint16_t year) {
    return (year % 4 == 0);
}

uint8_t RTC::daysInMonth(uint16_t year, uint8_t month) {
    uint8_t days;

    days = pgm_read_byte(daysArray + month - 1);

    if ((month == 2) && isLeapYear(year)) {
        ++days;
    }

    return days;
}

uint16_t RTC::date2days(uint16_t year, uint8_t month, uint8_t day) {
    year = year - 2000;

    uint16_t days16 = day;

    for (uint8_t i = 1; i < month; ++i) {
        days16 += pgm_read_byte(daysArray + i - 1);
    }

    if ((month == 2) && isLeapYear(year)) {
        ++days16;
    }

    return days16 + 365 * year + (year + 3) / 4 - 1;
}

uint32_t RTC::unixtime(void) {
    uint32_t u;

    u = time2long(date2days(t.year, t.month, t.day), t.hour, t.minute, t.second);
    u += 946681200;

    return u;
}

uint8_t RTC::conv2d(const char* p) {
    uint8_t v = 0;

    if ('0' <= *p && *p <= '9') {
        v = *p - '0';
    }

    return 10 * v + *++p - '0';
}

uint8_t RTC::dow(uint16_t y, uint8_t m, uint8_t d) {
    uint8_t dow;

    y -= m < 3;
    dow = ((y + y/4 - y/100 + y/400 + pgm_read_byte(dowArray+(m-1)) + d) % 7);

    if (dow == 0) {
        return 7;
    }

    return dow;
}
