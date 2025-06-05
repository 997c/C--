#ifndef CALENDAR_H
#define CALENDAR_H

#include "date.h"
#include <vector>
#include <string>

class Calendar {
private:
    Date currentDate;
    std::vector<std::pair<Date, std::string>> events;

    void printMonthHeader() const;
    void printMonthDays() const;

public:
    Calendar();
    explicit Calendar(const Date& date);
    
    void setDate(const Date& date);
    Date getDate() const { return currentDate; }
    
    void display() const;
    void displayMonth() const;
    void displayYear();
    
    void addEvent(const Date& date, const std::string& event);
    void removeEvent(const Date& date, const std::string& event);
    std::vector<std::string> getEvents(const Date& date) const;
    
    void nextMonth();
    void previousMonth();
    void nextYear();
    void previousYear();
};

#endif // CALENDAR_H