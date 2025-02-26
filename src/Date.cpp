#include "Date.hpp"
#include <sstream>  // For string stream formatting
#include <ctime>

// Constructor
Date::Date(int year, int month, int day) : year(year), month(month), day(day) {}

// Compare function: negative if earlier, positive if later, 0 if same
int Date::compareTo(const Date& other) const {
    if (year != other.year) return year - other.year;
    if (month != other.month) return month - other.month;
    return day - other.day;
}

// Convert the date to a "total days since reference point" (e.g., 0000-01-01)
int Date::toDays() const {
    int y = year;
    int m = month;
    int d = day;

    // Account for leap years
    int leapYears = (y / 4) - (y / 100) + (y / 400);
    
    // Days per month (non-leap year)
    static const int daysPerMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    // Convert years to days
    int totalDays = y * 365 + leapYears;

    // Convert months to days
    for (int i = 0; i < m - 1; i++) {
        totalDays += daysPerMonth[i];
    }

    // Add days
    totalDays += d;

    // If the current year is a leap year and the date is after February, add an extra day
    if (m > 2 && ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0))) {
        totalDays++;
    }

    return totalDays;
}

// Calculate the difference in days between two dates
int Date::daysBetween(const Date& other) const {
    return other.toDays() - this->toDays();
}

// Display the date in YYYY-MM-DD format
std::string Date::toString() const {
    std::ostringstream oss;
    oss  << year << "-"
              << (month < 10 ? "0" : "") << month << "-"
              << (day < 10 ? "0" : "") << day;
    return oss.str();
}

// Get today's date in Date format
Date Date::today() {
    std::time_t t = std::time(nullptr);  // Get current time
    std::tm* now = std::localtime(&t);   // Convert to local time structure

    return Date(now->tm_year + 1900, now->tm_mon + 1, now->tm_mday);  // Convert to Date
}
