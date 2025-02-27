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
Patient::Patient(string name, string phone, Date dob, string disease, string treatment) : patientID(nextID++), name(name), phoneNumber(phone), DOB(dob), disease(disease), treatment(treatment), admissionDate(Date::today()), dischargeDate(0, 0, 0) {}

// Copy constructor, I don't know if we'll need one but hey
Patient::Patient(const Patient& p) : patientID(p.patientID), name(p.name), phoneNumber(p.phoneNumber), DOB(p.DOB), disease(p.disease), treatment(p.treatment), admissionDate(p.admissionDate), dischargeDate(p.dischargeDate) {}

// Move constructor, I believe we will need this to move patient to another hospital, depending on how they are related and stored in Hospital. If there is a vector or something in Hospital that stores the patients, we can just move the Patient to that vector without having to make another Patient instance.
Patient::Patient(Patient&& p) : patientID(move(p.patientID)), name(move(p.name)), phoneNumber(move(p.phoneNumber)), DOB(move(p.DOB)), disease(move(p.disease)), treatment(move(p.treatment)), admissionDate(move(p.admissionDate)), dischargeDate(move(p.dischargeDate)) {} 

// Discharge Patient, set their discharge date to today.
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
    cout << "===============================\n"
              << "      Patient Information\n"
              << "===============================\n"
              << "ID           : " << patientID << "\n"
              << "Name         : " << name << "\n"
              << "DOB          : " << DOB.toString() << "\n"
              << "Disease      : " << disease << "\n"
              << "Treatment    : " << treatment << "\n"
              << "Primary      : " << "Dr. " << getPrimaryDoctor()->getName() << "\n"
              << "Admitted on  : " << admissionDate.toString() << "\n"
              << "Discharged on: ";

    if (dischargeDate.compareTo(Date()) == 0) {
        cout << YELLOW << "Pending" << RESET;
    } else {
        cout << GREEN << dischargeDate.toString() << RESET;
    }

    cout << "\n-------------------------------\n"
              << "Total Days Admitted: " << getDaysAdmitted() << " day(s)\n"
              << "===============================\n";
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