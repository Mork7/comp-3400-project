#ifndef PATIENT_H
#define PATIENT_H
#include "Date.hpp"

class Patient {
// Private Member
private:
    // use static because this will ensure the patientID is unique. All Patient classes will share this variable.
    static int nextID;
    int patientID;
    std::string name;
    std::string phoneNumber;
    Date DOB;
    std::string disease;
    std::string treatment;
    Date admissionDate;
    Date dischargeDate;

// Public Members
public:
    Patient(std::string name, std::string phoneNumber, Date dob, std::string disease, std::string treatment);
    void discharge(Date discharge);
    int getDaysAdmitted() const;
    void displayInfo() const;
    Date getAdmissionDate() const;
    int getPatientID() const;
    Date getDischargeDate() const;
};

#endif