#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "Date.hpp"
#include <string>

class Hospital; // forward delcaration

class Employee {
    protected:
        static int nextID;      
        int employeeID;         
        std::string name;     
        std::string phoneNumber;
        Date DOB;
        std::string position;  
        Hospital* hospital;

    public:
        explicit Employee(std::string name, Date dob, std::string phoneNumber, std::string position, Hospital* hospital);
        virtual ~Employee() = default;  // virtual destructor for inheritance, virtual allows a method to be overridden by derived classes

        int getEmployeeID() const;
        std::string getName() const;
        Date getDOB() const;
        std::string getPhoneNumber() const;
        std::string getPosition() const;
        Hospital* getHospital() const;  // Allow access to the associated hospital
        // Doctors and Nurses can override this to print info, this const = 0 makes
        virtual void displayInfo() const = 0; 
};

#endif