#include "date.h"
#include <ctime>
#include <sstream>
#include <iomanip>
#include <stdexcept>

Date::Date(int d, int m, int y) : day(d), month(m), year(y) {
    if (!isValidDate()) {
        throw std::invalid_argument("Invalid date");
    }
}

bool Date::isLeapYear() const {
    if (year % 4 != 0) return false;
    if (year % 100 != 0) return true;
    return (year % 400 == 0);
}

int Date::daysInMonth() const {
    if (month == 2) {
        return isLeapYear() ? 29 : 28;
    }
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    }
    return 31;
}

bool Date::isValidDate() const {
    if (year < 1) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > daysInMonth()) return false;
    return true;
}

void Date::setDate(int d, int m, int y) {
    day = d;
    month = m;
    year = y;
    if (!isValidDate()) {
        throw std::invalid_argument("Invalid date");
    }
}

void Date::nextDay() {
    day++;
    if (day > daysInMonth()) {
        day = 1;
        month++;
        if (month > 12) {
            month = 1;
            year++;
        }
    }
}

void Date::previousDay() {
    day--;
    if (day < 1) {
        month--;
        if (month < 1) {
            month = 12;
            year--;
        }
        day = daysInMonth();
    }
}

std::string Date::toString() const {
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << day << "/"
        << std::setw(2) << std::setfill('0') << month << "/"
        << year;
    return oss.str();
}

std::string Date::getDayOfWeek() const {
    tm timeinfo = {0};
    timeinfo.tm_year = year - 1900;
    timeinfo.tm_mon = month - 1;
    timeinfo.tm_mday = day;
    mktime(&timeinfo);
    
    const char* days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", 
                          "Thursday", "Friday", "Saturday"};
    return days[timeinfo.tm_wday];
}

int Date::compareDates(const Date& d1, const Date& d2) {
    if (d1.year != d2.year) return d1.year - d2.year;
    if (d1.month != d2.month) return d1.month - d2.month;
    return d1.day - d2.day;
}