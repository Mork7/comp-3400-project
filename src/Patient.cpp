#include "Patient.hpp"
#include "Doctor.hpp"
#include <iostream>

// Color codes for nice terminal display
#define RESET   "\033[0m"
#define YELLOW  "\033[33m"
#define GREEN  "\033[32m"

using namespace std;

// Initialize static variable
int Patient::nextID = 1000;  // Start patient IDs from 1000

// Patient Constructor, will increment nextID and set the patientID
Patient::Patient(string name, string phone, Date dob, string condition, string treatment) : patientID(nextID++), name(name), phoneNumber(phone), DOB(dob), condition(condition), treatment(treatment), admissionDate(Date::today()), dischargeDate(0, 0, 0) {}

// Copy constructor, I don't know if we'll need one but hey
Patient::Patient(const Patient& p) : patientID(p.patientID), name(p.name), phoneNumber(p.phoneNumber), DOB(p.DOB), condition(p.condition), treatment(p.treatment), admissionDate(p.admissionDate), dischargeDate(p.dischargeDate) {}

// Move constructor, I believe we will need this to move patient to another hospital, depending on how they are related and stored in Hospital. If there is a vector or something in Hospital that stores the patients, we can just move the Patient to that vector without having to make another Patient instance.
Patient::Patient(Patient&& p) : patientID(std::move(p.patientID)), name(std::move(p.name)), phoneNumber(std::move(p.phoneNumber)), DOB(std::move(p.DOB)), condition(std::move(p.condition)), treatment(std::move(p.treatment)), admissionDate(std::move(p.admissionDate)), dischargeDate(std::move(p.dischargeDate)) {} 

// Discharge Patient, set their discharge date to today and get total owed
void Patient::discharge() {
    dischargeDate = Date::today();
}

// Get the amount of days admitted for billing purposes. Patients are billed at least 1 day minimum
int Patient::getDaysAdmitted() const {
    Date today = Date::today();
    
    if (dischargeDate.compareTo(Date(0, 0, 0)) == 0) {
        return max(1, admissionDate.daysBetween(today));
    }
    return max(1, admissionDate.daysBetween(dischargeDate));
}

// Display the patient information in a nice readable format.
void Patient::displayInfo() const {
    cout << YELLOW << "===============================\n"
            << "      Patient Information\n"
            << "===============================\n" << RESET
            << "ID            : " << patientID << "\n"
            << "Name          : " << name << "\n"
            << "DOB           : " << DOB.toString() << "\n"
            << "Condition     : " << condition << "\n"
            << "Treatment     : " << treatment << "\n"
            << "Primary Doctor: " << "Dr. " << getPrimaryDoctor()->getName() << "\n"
            << "Admitted on   : " << admissionDate.toString() << "\n"
            << "Discharged on : ";

    if (dischargeDate.compareTo(Date()) == 0) {
        cout << YELLOW << "Pending" << RESET;
    } else {
        cout << GREEN << dischargeDate.toString() << RESET;
    }

    cout << YELLOW << "\n-------------------------------\n"
            << GREEN << "Total Days Admitted: " << getDaysAdmitted() << " day(s)\n" << RESET
            << YELLOW << "===============================\n" << RESET;
}

// Get Discharge Date
Date Patient::getDischargeDate() const {
    return this->dischargeDate;
}

// Get Admission Date
Date Patient::getAdmissionDate() const {
    return this->admissionDate;
}

// Get Patient ID
int Patient::getPatientID() const {
    return this->patientID;
}

// Get patient name
string Patient::getName() const{
    return name;
}

// Set primary doctor, in-case of transfers etc.
void Patient::setPrimaryDoctor(Doctor* doctor){
    primaryDoctor = doctor;
}

// Get primary dcotor
Doctor* Patient::getPrimaryDoctor() const {
    return primaryDoctor;
}