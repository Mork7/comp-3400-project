#ifndef PATIENT_H
#define PATIENT_H
#include "Date.hpp"
#include <string>

class Doctor;

class Patient {
// Private Members
private:
    // use static because this will ensure the patientID is unique. All Patient classes will share this variable.
    static int nextID;
    int patientID;
    std::string name;
    std::string phoneNumber;
    Date DOB;
    std::string condition;
    std::string treatment;
    Date admissionDate;
    Date dischargeDate;
    Doctor* primaryDoctor;

// Public Members
public:
    Patient(std::string name, std::string phoneNumber, Date dob, std::string condition, std::string treatment);
    Patient(const Patient& p);
    Patient(Patient&& p);
    void discharge();
    void displayInfo() const;
    Date getAdmissionDate() const;
    int getDaysAdmitted() const;
    int getPatientID() const;
    std::string getName() const;
    Date getDischargeDate() const;
    Doctor* getPrimaryDoctor() const;
    void setPrimaryDoctor(Doctor* primaryDoc);
};

#endif