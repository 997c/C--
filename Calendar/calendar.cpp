#include "calendar.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

Calendar::Calendar() : currentDate(Date()) {}

Calendar::Calendar(const Date& date) : currentDate(date) {}

void Calendar::setDate(const Date& date) {
    currentDate = date;
}

void Calendar::printMonthHeader() const {
    std::string months[] = {"January", "February", "March", "April", "May", "June",
                           "July", "August", "September", "October", "November", "December"};
    
    std::cout << "\n " << months[currentDate.getMonth() - 1] << " " << currentDate.getYear() << "\n";
    std::cout << " Su Mo Tu We Th Fr Sa\n";
}

void Calendar::printMonthDays() const {
    // Get the first day of the month and its weekday
    Date firstDayOfMonth(1, currentDate.getMonth(), currentDate.getYear());
    std::string firstDayWeekday = firstDayOfMonth.getDayOfWeek();
    
    // Find the position (0-6) of the first day
    int startPos = 0;
    const char* days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", 
                         "Thursday", "Friday", "Saturday"};
    for (int i = 0; i < 7; ++i) {
        if (firstDayWeekday == days[i]) {
            startPos = i;
            break;
        }
    }
    
    // Print leading spaces
    for (int i = 0; i < startPos; ++i) {
        std::cout << "   ";
    }
    
    // Print the days
    Date tempDate(1, currentDate.getMonth(), currentDate.getYear());
    int daysInMonth = tempDate.getDaysInMonth();
    for (int day = 1; day <= daysInMonth; ++day) {
        std::cout << std::setw(3) << day;
        if ((day + startPos) % 7 == 0 || day == daysInMonth) {
            std::cout << "\n";
        }
    }
}

void Calendar::display() const {
    displayMonth();
}

void Calendar::displayMonth() const {
    printMonthHeader();
    printMonthDays();
}

void Calendar::displayYear() {
    int originalMonth = currentDate.getMonth();
    int originalYear = currentDate.getYear();
    
    for (int month = 1; month <= 12; ++month) {
        currentDate.setDate(1, month, originalYear);
        displayMonth();
    }
    
    // Restore original month
    currentDate.setDate(1, originalMonth, originalYear);
}

void Calendar::addEvent(const Date& date, const std::string& event) {
    events.emplace_back(date, event);
    // Sort events by date
    std::sort(events.begin(), events.end(), 
        [](const std::pair<Date, std::string>& a, const std::pair<Date, std::string>& b) {
            return Date::compareDates(a.first, b.first) < 0;
        });
}

void Calendar::removeEvent(const Date& date, const std::string& event) {
    events.erase(std::remove_if(events.begin(), events.end(),
        [&date, &event](const std::pair<Date, std::string>& item) {
            return Date::compareDates(item.first, date) == 0 && item.second == event;
        }), events.end());
}

std::vector<std::string> Calendar::getEvents(const Date& date) const {
    std::vector<std::string> result;
    for (const auto& eventPair : events) {
        if (Date::compareDates(eventPair.first, date) == 0) {
            result.push_back(eventPair.second);
        }
    }
    return result;
}

void Calendar::nextMonth() {
    int newMonth = currentDate.getMonth() + 1;
    int newYear = currentDate.getYear();
    if (newMonth > 12) {
        newMonth = 1;
        newYear++;
    }
    currentDate.setDate(1, newMonth, newYear);
}

void Calendar::previousMonth() {
    int newMonth = currentDate.getMonth() - 1;
    int newYear = currentDate.getYear();
    if (newMonth < 1) {
        newMonth = 12;
        newYear--;
    }
    currentDate.setDate(1, newMonth, newYear);
}

void Calendar::nextYear() {
    currentDate.setDate(1, currentDate.getMonth(), currentDate.getYear() + 1);
}

void Calendar::previousYear() {
    currentDate.setDate(1, currentDate.getMonth(), currentDate.getYear() - 1);
}