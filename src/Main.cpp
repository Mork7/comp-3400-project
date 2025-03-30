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
void viewPatients(const unordered_map<int, shared_ptr<Patient>>& patients);

int main() {
    cout << fixed << setprecision(2);
    
    //======================== HOSPITAL TESTS =====================
    auto hospitals = setupHospitals();
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
    auto pharmacies = setupPharmacies();
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
    return 0;

    //========================= TERMINAL UI =========================
    unordered_map<int, shared_ptr<Patient>> patients;  
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
            viewPatients(patients);  
        }
        else if (choice == 3) {
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
    cout << "3. Exit" << endl;
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

//Function to view patients.
void viewPatients(const unordered_map<int, shared_ptr<Patient>>& patients) {
    cout << "\n==================== Patients ====================" << endl;
    int patientID;
    cout << "Enter Patient ID to view details: ";
    cin >> patientID;

    auto it = patients.find(patientID);
    if (it != patients.end()) {
        it->second->displayInfo();  //display patient details
    }
    else {
        cout << "Patient not found!" << endl;
    }
}

