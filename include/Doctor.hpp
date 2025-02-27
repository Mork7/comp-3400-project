#ifndef DOCTOR_H
#define DOCTOR_H
#include "Employee.hpp"
#include "Patient.hpp"
#include <vector>

class Hospital; // forward delcaration

class Doctor : public Employee {
private:
    // Doctor will take care of these patients
    std::vector<Patient*> patients;  

public:
    explicit Doctor(std::string name, Date dob, std::string phoneNumber, Hospital* hospital);

    void assignPatient(Patient* patient, bool isPrimary);
    void removePatient(int patientID);
    void dischargePatient(int patientID);
    void displayInfo() const override;
    void listPatients() const; 

};

#endif