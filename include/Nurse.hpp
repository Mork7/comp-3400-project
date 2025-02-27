#ifndef NURSE_H
#define NURSE_H

#include "Employee.hpp"
#include "Patient.hpp"
#include <vector>

class Nurse : public Employee {
private:
    std::vector<Patient*> assignedPatients;  // Nurses can be assigned patients
    
public:
    Nurse(std::string name, Date dob, std::string phoneNumber, Hospital* hospital);

    void assignPatient(Patient* patient);
    void removePatient(int patientID);
    void displayInfo() const;
    bool canTakePatient() const;
};

#endif
