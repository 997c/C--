#include "calendar.h"
#include <iostream>
#include <string>

void displayMenu() {
    std::cout << "\nCalendar Application\n";
    std::cout << "1. View Current Month\n";
    std::cout << "2. View Current Year\n";
    std::cout << "3. Next Month\n";
    std::cout << "4. Previous Month\n";
    std::cout << "5. Next Year\n";
    std::cout << "6. Previous Year\n";
    std::cout << "7. Add Event\n";
    std::cout << "8. View Events\n";
    std::cout << "9. Remove Event\n";
    std::cout << "0. Exit\n";
    std::cout << "Choose an option: ";
}

int main() {
    Calendar calendar;
    int choice;
    
    do {
        displayMenu();
        std::cin >> choice;
        std::cin.ignore(); // Clear newline
        
        switch (choice) {
            case 1:
                calendar.displayMonth();
                break;
            case 2:
                calendar.displayYear();
                break;
            case 3:
                calendar.nextMonth();
                calendar.displayMonth();
                break;
            case 4:
                calendar.previousMonth();
                calendar.displayMonth();
                break;
            case 5:
                calendar.nextYear();
                calendar.displayMonth();
                break;
            case 6:
                calendar.previousYear();
                calendar.displayMonth();
                break;
            case 7: {
                int day, month, year;
                std::string event;
                
                std::cout << "Enter day (1-31): ";
                std::cin >> day;
                std::cout << "Enter month (1-12): ";
                std::cin >> month;
                std::cout << "Enter year: ";
                std::cin >> year;
                std::cin.ignore(); // Clear newline
                
                std::cout << "Enter event description: ";
                std::getline(std::cin, event);
                
                try {
                    calendar.addEvent(Date(day, month, year), event);
                    std::cout << "Event added successfully.\n";
                } catch (const std::invalid_argument& e) {
                    std::cout << "Error: " << e.what() << "\n";
                }
                break;
            }
            case 8: {
                int day, month, year;
                std::cout << "Enter day (1-31): ";
                std::cin >> day;
                std::cout << "Enter month (1-12): ";
                std::cin >> month;
                std::cout << "Enter year: ";
                std::cin >> year;
                
                try {
                    Date date(day, month, year);
                    auto events = calendar.getEvents(date);
                    if (events.empty()) {
                        std::cout << "No events on " << date.toString() << "\n";
                    } else {
                        std::cout << "Events on " << date.toString() << ":\n";
                        for (const auto& event : events) {
                            std::cout << "- " << event << "\n";
                        }
                    }
                } catch (const std::invalid_argument& e) {
                    std::cout << "Error: " << e.what() << "\n";
                }
                break;
            }
            case 9: {
                int day, month, year;
                std::string event;
                
                std::cout << "Enter day (1-31): ";
                std::cin >> day;
                std::cout << "Enter month (1-12): ";
                std::cin >> month;
                std::cout << "Enter year: ";
                std::cin >> year;
                std::cin.ignore(); // Clear newline
                
                std::cout << "Enter event description to remove: ";
                std::getline(std::cin, event);
                
                try {
                    calendar.removeEvent(Date(day, month, year), event);
                    std::cout << "Event removed if it existed.\n";
                } catch (const std::invalid_argument& e) {
                    std::cout << "Error: " << e.what() << "\n";
                }
                break;
            }
            case 0:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
    
    return 0;
}