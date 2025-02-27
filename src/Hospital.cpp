#include "Hospital.hpp"
#include <string>
#include <iostream>

using namespace std;

Hospital::Hospital(string name) : name(name) {}

void Hospital::addDoctor(unique_ptr<Employee> doctor) {
    doctors.push_back(move(doctor));
}

void Hospital::addNurse(unique_ptr<Employee> nurse) {
    nurses.push_back(move(nurse));
}

void Hospital::addPatient(unique_ptr<Patient> patient) {
    patients.push_back(move(patient));
}

string Hospital::getName(){
    return name;
}

void Hospital::printPatients(){
    cout << "Patients: " << endl;
    for(auto& patient : patients) {
        // Assuming Patient has a method to print its details
        patient->displayInfo();
    }
}
