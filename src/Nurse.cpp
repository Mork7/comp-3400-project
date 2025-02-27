#include "Nurse.hpp"
#include <iostream>
#include "Hospital.hpp"
#include <algorithm>

#define RED "\033[31m" 
#define YELLOW "\033[33m" 
#define RESET "\033[0m"

using namespace std;

// Nurse constructor
Nurse::Nurse(std::string name, Date dob, std::string phoneNumber, Hospital* hospital)
    : Employee(name, dob, phoneNumber, "Nurse", hospital) {}

// Assign a patient to the nurse (max 2 per nurse)
void Nurse::assignPatient(Patient* patient) {
    if (assignedPatients.size() < 2) {  // nurses can only handle two patients
        assignedPatients.push_back(patient);
        cout << "Nurse " << name << " is now taking care of Patient " << patient->getPatientID() << ".\n";
    } else {
        cout << "Nurse " << name << " is at capacity (2 patients max). Patient not transferred.\n";
    }
}

// Remove a pateint from nurse’s care
void Nurse::removePatient(int patientID) {
    auto iterator = remove_if(assignedPatients.begin(), assignedPatients.end(),
        [&](Patient* p) { return p->getPatientID() == patientID; });

    if (iterator != assignedPatients.end()) {
        assignedPatients.erase(iterator, assignedPatients.end());
        cout << "Nurse " << name << " is no longer assigned to Patient "  << patientID << " ("<< hospital->getPatientById(patientID)->getName() << ").\n";
    }
}

// Print nurse info
void Nurse::displayInfo() const {
    cout << "Nurse ID: " << employeeID << " - " << name << "\n";
    if (assignedPatients.empty()) {
        cout << RED <<  "No assigned patients." << endl;
    } else {
        cout << "Patients under care:\n";
        for (const auto& patient : assignedPatients) {
            cout << YELLOW "  - Patient ID: " << patient->getPatientID() << RESET << endl;;
        }
    }
}

bool Nurse::canTakePatient() const {
    return assignedPatients.size() < 2;
}