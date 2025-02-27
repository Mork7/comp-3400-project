#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include "Date.hpp"
#include <string>

class Employee {
private:
    static int nextID;
    int employeeID;
    std::string name;
    std::string phoneNumber;
    Date DOB;
    std::string position;

public:
    Employee(std::string name, Date dob, std::string phoneNumber, std::string position);

    int getEmployeeID() const;
    std::string getName() const;
    Date getDOB() const;
    std::string getPhoneNumber() const;
    std::string getPosition() const;
    void setPosition(std::string newPosition);
};

#endif

