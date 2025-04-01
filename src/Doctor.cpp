#include "Doctor.hpp"
#include "Hospital.hpp"
#include <iostream>
#include <algorithm>

#define RED "\033[31m"  // Red for warnings
#define YELLOW "\033[33m" 
#define RESET "\033[0m"


using namespace std;

// Constructor for Doctors
Doctor::Doctor(string name, Date dob, string phoneNumber, Hospital* hospital)
    : Employee(name, dob, phoneNumber, "Doctor", hospital) {}

// Assign a patient to the doctor
void Doctor::assignPatient(Patient* patient, bool isPrimary) {
    if (isPrimary) {
        patient->setPrimaryDoctor(this);
    }
    patients.push_back(patient);
    cout << "Doctor " << name << " is now treating Patient " << patient->getPatientID() << ".\n";
}

// Removal of patient from doctors care, in case of transfer
void Doctor::removePatient(int patientID) {
    auto it = remove_if(patients.begin(), patients.end(),
        [&](Patient* p) { return p->getPatientID() == patientID; });

    if (it != patients.end()) {
        patients.erase(it, patients.end());
        cout << "Doctor " << name << " is no longer treating Patient " << patientID << ".\n";
    }
}

// Doctor decides when to discharge the patient, dischargePatientFromHospital takes care of hospitals records, this one takes care of Docotr and Nurse records.
void Doctor::dischargePatient(int patientID) {
    // if the doctor isnt assigned to a hospital we have an issue
    if (!hospital) {
        cerr << "\033[31mError:\033[0m Doctor " << name << " is not assigned to any hospital.\n";
        return;
    }

    Doctor* registeredDoctor = hospital->getDoctorById(employeeID);
    if (!registeredDoctor) {
        cerr << "\033[31mError:\033[0m Doctor " << name << " does not work at " << hospital->getName() << " and cannot discharge patients.\n";
        return;
    } 

    auto iterator = find_if(patients.begin(), patients.end(),
        [&](Patient* p) { return p->getPatientID() == patientID; });

    if (iterator != patients.end()) {
        cout << "Doctor " << name << " is discharging Patient " << patientID << ".\n";

        if (hospital->getPatientById(patientID)) {
            hospital->dischargePatientFromHospital(patientID);
            patients.erase(iterator);

            // Remove the patient from all assigned nurses
            for (auto& nurse : hospital->getNurses()) {
                nurse->removePatient(patientID);
            }
        } else {
            cerr << "\033[31mError:\033[0m Patient " << patientID << " is not in " << hospital->getName() << ".\n";
        }
    } else {
        cerr << "\033[31mError:\033[0m Doctor " << name << " is not treating Patient " << patientID << ".\n";
    }
}

// Print doctor info
void Doctor::displayInfo() const {
    cout << "Doctor ID: " << employeeID << " - " << name << "\n";
    if (patients.empty()) {
        cout << RED <<  "  - No assigned patients." << RESET << endl;
    } else {
        listPatients();
    }
}

// List Patients under doctors care
void Doctor::listPatients() const {
    if (patients.empty()) {
        std::cout << "No patients assigned.\n";
    } else {
        for (const auto& patient : patients) {
            std::cout << YELLOW << "  - Patient ID: " << patient->getPatientID() << " (" << patient->getName() << ")" << RESET << endl;
        }
    }
}
