#ifndef DATE_H
#define DATE_H

#include <iostream>

class Date {
private:
    int year;
    int month;
    int day;
    // Helper function when getting the daysBetween
    int toDays() const;

public:
    Date(int year, int month, int day);
    int compareTo(const Date& other) const;
    int daysBetween(const Date& other) const;
    std::string toString() const; 

    static Date today();
};

#endif
