#include "Patient.hpp"
#include <iostream>

// Color codes for nice terminal display
#define RESET   "\033[0m"
#define YELLOW  "\033[33m"
#define GREEN  "\033[32m"


// Initialize static variable
int Patient::nextID = 1000;  // Start patient IDs from 1000

// Patient constructor
Patient::Patient(std::string name, std::string phone, Date dob, std::string disease, std::string treatment)
    : patientID(nextID++), name(name), phoneNumber(phone), DOB(dob), disease(disease), treatment(treatment), admissionDate(Date::today()), dischargeDate(0, 0, 0) {}

// Dischange patient 
// TODO: A doctor discharges a patient, so when a doctor 
void Patient::discharge(Date discharge) {
    dischargeDate = discharge;
}

// Get the amount of days admitted for billing purposes when we come across it.
int Patient::getDaysAdmitted() const {
    // If the patient has not been discharged, use today's date instead
    if (dischargeDate.compareTo(Date(0, 0, 0)) == 0) {
        return admissionDate.daysBetween(Date::today());
    }
    return admissionDate.daysBetween(dischargeDate);
}

// Display the patient information in a nice readable format.
void Patient::displayInfo() const {
    std::cout << "===============================\n"
              << "      Patient Information\n"
              << "===============================\n"
              << "ID           : " << patientID << "\n"
              << "Name         : " << name << "\n"
              << "DOB          : " << DOB.toString() << "\n"
              << "Disease      : " << disease << "\n"
              << "Treatment    : " << treatment << "\n"
              << "Admitted on  : " << admissionDate.toString() << "\n"
              << "Discharged on: ";

    if (dischargeDate.compareTo(Date(0, 0, 0)) == 0) {
        std::cout << YELLOW << "Pending" << RESET;
    } else {
        std::cout << GREEN << dischargeDate.toString() << RESET;
    }

    std::cout << "\n-------------------------------\n"
              << "Total Days Admitted: " << getDaysAdmitted() << " days\n"
              << "===============================\n";
}
