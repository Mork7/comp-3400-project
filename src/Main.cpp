#include "Setup.hpp"
#include <iostream>
#include <iomanip>
#include <cassert>
#include <map>
#include <unordered_map> 
#include <memory>

/**
 *==================== Hospitals =====================
 *  [x] - 5 different locations
 *  [x] - Patient can be admitted -> Hospital.cpp -> void admitPatient(:unique_ptr<Patient> patient);
 *  [x] - Patients can be relocated -> Hospital.cpp -> void transferPatient(Hospital& newHospital, int patientID);
 *  [x] - Each Hospital can be identified -> Hospital.hpp -> std::string name;
 *  [x] - Hospitals can handle up to 20 admissions -> Hospital.cpp -> if (numAdmittedPatients < 20) (Line 37)
 *=================== Pharmacies =====================
 *  [x] - Each pharmacy has an id and name
 *  [x] - Pharmacy bills hospital directly -> Pharmacy.cpp -> double requestMedication(Hospital& hospital, std::string medName, int quantity);
 * =================== Patients ======================
 *  [x] - Each patient has a unique ID -> Patient.hpp -> static int nextID; & int patientID;
 *  [x] - Full description of patient details, phone number and condition/treatment -> Patient.hpp -> Lines 14-18
 *  [x] - Patients will be billed on number of days they are admitted 
 *  [x] - Patient will remain admitted until a doctor discharges them -> Doctor.cpp -> void dischargePatient(int patientID);
 * ==================== Doctors ======================
 *  [x] - Each Doctor has a unique ID -> Employee.hpp -> static int nextID & int EmployeeID
 *  [x] - Doctors treat many patients but only one is primary doctor -> Patient.hpp -> Doctor* primaryDoctor; & Doctor.cpp -> void assignPatient(Patient* patient, bool isPrimary);
 * ==================== Nurses =======================
 * [x] - Each Nurse has a unique ID -> Employee.hpp -> static int nextID & int EmployeeID
 * [x] - Minimum of 5 Nurses per hospital
 * [x] - Each Nurse responsible for care of at most 2 patients -> Nurse.cpp -> void Nurse::assignPatient(Patient* patient) -> if (assignedPatients.size() < 2) (Line 18)
*/

using namespace std;

void displayMainMenu();
void viewHospitals(const unordered_map<string, unique_ptr<Hospital>>& hospitals);
void viewPatients(const unordered_map<string, unique_ptr<Hospital>>& hospitals);
void transferPatient(unordered_map<string, unique_ptr<Hospital>>& hospitals);
void dischargePatient(unordered_map<string, unique_ptr<Hospital>>& hospitals);
void requestMedication(unordered_map<string, unique_ptr<Hospital>>& hospitals, 
                      unordered_map<string, unique_ptr<Pharmacy>>& pharmacies);

int main() {
    cout << fixed << setprecision(2);
    
    bool runTests = false; // Set to true when you want to run tests
    
    // Initialize hospitals 
    auto hospitals = setupHospitals();
    auto pharmacies = setupPharmacies();
    
    if (runTests) {
        //======================== HOSPITAL TESTS =====================
        // Get two hospitals for testing
        Hospital* morks = hospitals["Mork's"].get();
        Hospital* ryans = hospitals["Ryan's"].get();
        assert(morks != nullptr && "Test failed: Mork's hospital not found!");
        assert(ryans != nullptr && "Test failed: Ryan's hospital not found!");
        // Initial fund checks
        double initialFundsMorks = morks->getFunds();  // Set starting hospital funds
        double initialFundsRyans = ryans->getFunds();
        assert(morks->getFunds() == initialFundsMorks && "Test failed: Mork's initial funds incorrect!");
        assert(ryans->getFunds() == initialFundsRyans && "Test failed: Ryan's initial funds incorrect!");
        // Transfer patient check
        morks->transferPatient(*ryans, 1060);
        assert(ryans->getPatientById(1060) != nullptr && "Test failed: Ryan's never received patient!");
        assert(morks->getPatientById(1060) == nullptr && "Test failed: Mork's still owns patient!");
        
        // ================= PHARMACY TESTS ==================
        // Get a pharmacy
        Pharmacy* mediCorp = pharmacies["MediCorp"].get();
        assert(mediCorp != nullptr && "Test failed: MediCorp pharmacy not found!");
        
        // Test requestMedication
        double cost1 = mediCorp->requestMedication(*morks, "Ibuprofen", 10);
        assert(cost1 == 80.00 && "Test failed: Incorrect total cost for Ibuprofen!");
        assert(morks->getFunds() == initialFundsMorks - cost1 && "Test failed: Mork's funds did not decrease correctly!");
        
        double cost2 = mediCorp->requestMedication(*ryans, "Antibiotics", 5);
        assert(cost2 == 75.00 && "Test failed: Incorrect total cost for Antibiotics!");
        assert(ryans->getFunds() == initialFundsRyans - cost2 && "Test failed: Ryan's funds did not decrease correctly!");
        
        double cost3 = mediCorp->requestMedication(*ryans, "Percocet", 5);
        assert(cost3 == -1 && "Test failed: Invalid medication request should return -1!");
        assert(ryans->getFunds() == initialFundsRyans - cost2 && "Test failed: Ryan's funds should not change for invalid order!");

        // =============== PASSED ==================
        cout << "\nAll assertions passed successfully.\n";
    }
    
    //========================= TERMINAL UI =========================
    int choice;
    while (true) {
        // Display the main menu
        displayMainMenu();
        cin >> choice;

        // handle menu options
        if (choice == 1) {
            viewHospitals(hospitals);  
        }
        else if (choice == 2) {
            viewPatients(hospitals);  
        }
        else if (choice == 3) {
            transferPatient(hospitals);
        }
        else if (choice == 4) {
            dischargePatient(hospitals);
        }
        else if (choice == 5) {
            requestMedication(hospitals, pharmacies);
        }
        else if (choice == 6) {
            break;  
        }
        else {
            cout << "Invalid choice! Please try again." << endl;
        }
    }

    cout << "Thank you for using the Hospital Management System." << endl;
    return 0;
}

//Function to display the main menu
void displayMainMenu() {
    cout << "\nHospital Management System" << endl;
    cout << "1. View Hospitals" << endl;
    cout << "2. View Patients" << endl;
    cout << "3. Transfer Patient" << endl;
    cout << "4. Discharge Patient" << endl;
    cout << "5. Request Medication" << endl;
    cout << "6. Exit" << endl;
    cout << "Enter your choice: ";
}

//Function to view hospitals
void viewHospitals(const unordered_map<string, unique_ptr<Hospital>>& hospitals) {
    cout << "\n==================== Hospitals ====================" << endl;
    for (const auto& hospital : hospitals) {
        cout << "Hospital: " << hospital.first << endl;
        hospital.second->printPatients();  
        hospital.second->printDoctors();  
        hospital.second->printNurses(); 
        cout << "\n-------------------------------------------------" << endl;
    }
}

//Function to view patients
void viewPatients(const unordered_map<string, unique_ptr<Hospital>>& hospitals) {
    cout << "\n==================== Patients ====================" << endl;
    int patientID;
    cout << "Enter Patient ID to view details: ";
    cin >> patientID;

    // Search for the patient in each hospital
    bool found = false;
    for (const auto& [name, hospital] : hospitals) {
        Patient* patient = hospital->getPatientById(patientID);
        if (patient) {
            patient->displayInfo();
            found = true;
            break;
        }
    }
    
    if (!found) {
        cout << "Patient not found in any hospital!" << endl;
    }
}

// Function to transfer a patient between hospitals
void transferPatient(unordered_map<string, unique_ptr<Hospital>>& hospitals) {
    cout << "\n==================== Transfer Patient ====================" << endl;
    
    // Display all hospitals
    cout << "Available Hospitals:" << endl;
    int i = 1;
    for (const auto& [name, _] : hospitals) {
        cout << i++ << ". " << name << endl;
    }
    
    // Ask for source hospital
    string sourceHospital;
    cout << "Enter source hospital name: ";
    cin.ignore();
    getline(cin, sourceHospital);
    
    if (hospitals.find(sourceHospital) == hospitals.end()) {
        cout << "Hospital not found!" << endl;
        return;
    }
    
    // Ask for patient ID
    int patientID;
    cout << "Enter Patient ID to transfer: ";
    cin >> patientID;
    
    Patient* patient = hospitals[sourceHospital]->getPatientById(patientID);
    if (!patient) {
        cout << "Patient not found in " << sourceHospital << "!" << endl;
        return;
    }
    
    // Ask for destination hospital
    string destHospital;
    cout << "Enter destination hospital name: ";
    cin.ignore();
    getline(cin, destHospital);
    
    if (hospitals.find(destHospital) == hospitals.end() || sourceHospital == destHospital) {
        cout << "Invalid destination hospital!" << endl;
        return;
    }
    
    // Transfer patient
    hospitals[sourceHospital]->transferPatient(*hospitals[destHospital], patientID);
    cout << "Patient " << patientID << " transferred from " << sourceHospital 
         << " to " << destHospital << "." << endl;
}

// Function to discharge a patient
void dischargePatient(unordered_map<string, unique_ptr<Hospital>>& hospitals) {
    cout << "\n==================== Discharge Patient ====================" << endl;
    
    int patientID;
    cout << "Enter Patient ID to discharge: ";
    cin >> patientID;
    
    // Find the patient in any hospital
    bool found = false;
    for (const auto& [name, hospital] : hospitals) {
        Patient* patient = hospital->getPatientById(patientID);
        if (patient) {
            found = true;
            // Get the primary doctor to discharge the patient
            Doctor* doctor = patient->getPrimaryDoctor();
            if (doctor) {
                doctor->dischargePatient(patientID);
                cout << "Patient " << patientID << " discharged by Dr. " << doctor->getName() << endl;
            } else {
                cout << "Patient has no primary doctor assigned!" << endl;
            }
            break;
        }
    }
    
    if (!found) {
        cout << "Patient not found in any hospital!" << endl;
    }
}

// Function to request medication from a pharmacy
void requestMedication(unordered_map<string, unique_ptr<Hospital>>& hospitals, 
                      unordered_map<string, unique_ptr<Pharmacy>>& pharmacies) {
    cout << "\n==================== Request Medication ====================" << endl;
    
    // Display all hospitals
    cout << "Available Hospitals:" << endl;
    int i = 1;
    for (const auto& [name, _] : hospitals) {
        cout << i++ << ". " << name << endl;
    }
    
    // Ask for hospital
    string hospitalName;
    cout << "Enter hospital name: ";
    cin.ignore();
    getline(cin, hospitalName);
    
    if (hospitals.find(hospitalName) == hospitals.end()) {
        cout << "Hospital not found!" << endl;
        return;
    }
    
    // Display all pharmacies
    cout << "Available Pharmacies:" << endl;
    i = 1;
    for (const auto& [name, _] : pharmacies) {
        cout << i++ << ". " << name << endl;
    }
    
    // Ask for pharmacy
    string pharmacyName;
    cout << "Enter pharmacy name: ";
    getline(cin, pharmacyName);
    
    if (pharmacies.find(pharmacyName) == pharmacies.end()) {
        cout << "Pharmacy not found!" << endl;
        return;
    }
    
    // Ask for medication name
    string medicationName;
    cout << "Enter medication name: ";
    getline(cin, medicationName);
    
    // Ask for quantity
    int quantity;
    cout << "Enter quantity: ";
    cin >> quantity;
    
    // Request medication
    double cost = pharmacies[pharmacyName]->requestMedication(*hospitals[hospitalName], medicationName, quantity);
    if (cost > 0) {
        cout << "Medication request successful. Total cost: $" << cost << endl;
    } else {
        cout << "Medication request failed!" << endl;
    }
}

