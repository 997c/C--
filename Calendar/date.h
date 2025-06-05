#ifndef DATE_H
#define DATE_H

#include <string>

class Date {
private:
    int day;
    int month;
    int year;

    bool isLeapYear() const;
    int daysInMonth() const;
    bool isValidDate() const;

public:
    Date(int d = 1, int m = 1, int y = 1900);
    
    void setDate(int d, int m, int y);
    void nextDay();
    void previousDay();
    
    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }
    int getDaysInMonth() const { return daysInMonth(); }
    
    std::string toString() const;
    std::string getDayOfWeek() const;
    
    static int compareDates(const Date& d1, const Date& d2);
};

#endif // DATE_H