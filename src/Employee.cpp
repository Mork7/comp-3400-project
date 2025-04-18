#include "Employee.hpp"
#include <iostream>

using namespace std;

// Initialize static variable for unique Employee IDs
int Employee::nextID = 1;

// Constructor
Employee::Employee(string name, Date dob, string phone, string position, Hospital* hospital)
    : employeeID(nextID++), name(std::move(name)), phoneNumber(std::move(phone)),
        DOB(std::move(dob)), position(std::move(position)), hospital(std::move(hospital)) {}

// Getters
int Employee::getEmployeeID() const {
    return employeeID;
}

string Employee::getName() const {
    return name;
}

Date Employee::getDOB() const {
    return DOB;
}

string Employee::getPhoneNumber() const {
    return phoneNumber;
}

string Employee::getPosition() const {
    return position;
}

Hospital* Employee::getHospital() const {
    return hospital;
}