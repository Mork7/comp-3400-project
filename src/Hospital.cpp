// Header files
#include "Hospital.hpp"
#include "Date.hpp"
#include "Doctor.hpp"
#include "Nurse.hpp"
#include "Patient.hpp"
// Includes
#include <cstdlib>  // for rand()
#include <ctime>    // for seeding random numbers
#include <string>
#include <algorithm>
#include <iostream>
// ANSI color codes
#define RESET   "\033[0m"
#define BLUE    "\033[34m" 
#define RED     "\033[31m"

using namespace std;

// Hospital constructor
Hospital::Hospital(string name) : name(name), numAdmittedPatients(0) {}

// Add doctor to hospital staff
void Hospital::addDoctor(unique_ptr<Doctor> doctor) {
    doctors.push_back(move(doctor));
}

// Add nurse to hospital staff
void Hospital::addNurse(unique_ptr<Nurse> nurse) {
    nurses.push_back(move(nurse));
}

// Add a patient to the hospital, we will assign a doctor at random to be the primary
void Hospital::admitPatient(unique_ptr<Patient> patient) {

    if (numAdmittedPatients < 20) {
        // Assign a primary doctor if one is available
        if (!doctors.empty()) {
            int randomDoctorIndex = rand() % doctors.size();
            Doctor* assignedDoctor = doctors[randomDoctorIndex].get();
            patient->setPrimaryDoctor(assignedDoctor);  // assign primary doctor
            assignedDoctor->assignPatient(patient.get(), true);  // tell doctor to track patient
        } else {
            cout << "Warning: No doctors available at " << name << ". Primary doctor not set.\n";
            patient->setPrimaryDoctor(nullptr);
        }

        // Check for available nurses before selecting one
        vector<Nurse*> availableNurses;
        for (auto& nurse : nurses) {
            if (nurse->canTakePatient()) {
                availableNurses.push_back(nurse.get());
            }
        }

        // Only assign a nurse if there are available ones
        if (!availableNurses.empty()) {
            int randomNurseIndex = rand() % availableNurses.size();
            availableNurses[randomNurseIndex]->assignPatient(patient.get());
        } else {
            cout << "Warning: No nurses available at " << name << ". No nurse assigned.\n";
        }
        
        // successfully add the patient to the hostpial
        patients.push_back(move(patient));
        numAdmittedPatients++;
    } else {
        cout << "Hospital at capacity, cannot add more Patients" << endl;
    }
}

// Get hospital Name
string Hospital::getName(){
    return name;
}

// Print Patients
void Hospital::printPatients() {
    cout << BLUE << "\n============================================================" << RESET << endl;
    cout << BLUE << "   📋 Patients in " << name << RESET << endl;
    cout << BLUE << "============================================================" << RESET << endl;
    
    if (patients.empty()) {
        cout << RED << "No patients currently admitted.\n" << RESET;
    } else {
        for (auto& patient : patients) {
            patient->displayInfo();
        }
    }
}

// Print Doctors
void Hospital::printDoctors() {
    cout << BLUE << "\n============================================================" << RESET << endl;
    cout << BLUE << "   🩺 Doctors in " << name << RESET << endl;
    cout << BLUE << "============================================================" << RESET << endl;
    
    if (doctors.empty()) {
        cout << RED << "No doctors available.\n" << RESET;
    } else {
        for (auto& doctor : doctors) {
            doctor->displayInfo();
        }
    }
}

// Print Nurses
void Hospital::printNurses() {
    cout << BLUE << "\n============================================================" << RESET << endl;
    cout << BLUE << "   🏥 Nurses in " << name << RESET << endl;
    cout << BLUE << "============================================================" << RESET << endl;

    if (nurses.empty()) {
        cout << RED << "No nurses available.\n" << RESET;
    } else {
        for (auto& nurse : nurses) {
            nurse->displayInfo();
        
        }
    }
}

// Discharge a patient from the hospital, this will be called by a doctor.
void Hospital::dischargePatientFromHospital(int patientID) {
    auto iterator = find_if(patients.begin(), patients.end(),
        [&](const unique_ptr<Patient>& patient) {
            return patient->getPatientID() == patientID;
        });

    if (iterator != patients.end()) {
        cout << "Discharging patient ID " << patientID << " (" << Hospital::getPatientById(patientID)->getName() << ") from " << name << "...\n";
        // whichever Patient the iterator is pointing at, call the discharge function.
        (*iterator)->discharge(); 
        // patients.erase(it); This will delete from the vector, but for now I like having the record in the Hospital records with the discharge date.
        numAdmittedPatients--;
    } else {
        cerr << "Error: Patient ID " << patientID << " not found in this hospital.\n";
    }
}

// Transfer a patient from one hospital to another by ID
void Hospital::transferPatient(Hospital& newHospital, int patientID) {
    auto iterator = remove_if(patients.begin(), patients.end(),
        [&](unique_ptr<Patient>& patient) {
            if (patient->getPatientID() == patientID) {

                // Store pointer before moving
                Patient* patientPtr = patient.get();  

                // Move ownership to the new hospital
                newHospital.admitPatient(move(patient));

                // Assign a new primary doctor from the new hospital
                if (!newHospital.doctors.empty()) {
                    patientPtr->setPrimaryDoctor(newHospital.doctors.front().get());  // assign first available doctor
                } else {
                    cout << "Warning: No doctors available at " << newHospital.getName() 
                         << ". Primary doctor not set.\n";
                    patientPtr->setPrimaryDoctor(nullptr); // Avoids accessing an empty vector
                }
                
                return true; 
            }
            return false;
        });

    if (iterator == patients.end()) {
        cerr << "Error: Patient ID " << patientID << " not found in this hospital.\n";
    } else {
        patients.erase(iterator, patients.end());  // Remove patient from old hospital
        numAdmittedPatients--;
        newHospital.numAdmittedPatients++;  // Update count in new hospital
    }
}

// Getter for the number of admitted patients, just in case
int Hospital::getNumAdmittedPatients(){
    return numAdmittedPatients;
}

// Get a single doctor by ID so we can use their methods
Doctor* Hospital::getDoctorById(int doctorID) {
    for (auto& doctor : doctors) {
        if (doctor->getEmployeeID() == doctorID) {
            return doctor.get(); 
        }
    }
    return nullptr;  
}

// Get a single nurse by ID so we can use their methods
Nurse* Hospital::getNurseById(int nurseID) {
    for (auto& nurse : nurses) {
        if (nurse->getEmployeeID() == nurseID) {
            return nurse.get(); 
        }
    }
    return nullptr;  
}

// Get a single doctor by ID so we can use their methods
Patient* Hospital::getPatientById(int patientID) {
    for (auto& patient : patients) {
        if (patient->getPatientID() == patientID) {
            return patient.get(); 
        }
    }
    return nullptr;  
}

// Getter for nurses
vector<unique_ptr<Nurse>>& Hospital::getNurses() {
    return nurses;
}

// Getter for doctors
vector<unique_ptr<Doctor>>& Hospital::getDoctors() {
    return doctors;
}

// Getter for patients
vector<unique_ptr<Patient>>& Hospital::getPatients() {
    return patients;
}