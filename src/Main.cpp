#include "Setup.hpp"
#include <iostream>
#include <iomanip>
#include <cassert>
#include <map>
#include <unordered_map> 
#include <memory>
#include <thread>
#include <chrono>
#include <limits>

// ANSI color codes
#define RESET   "\033[0m"
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLD    "\033[1m"
#define UNDERLINE "\033[4m"
#define BG_BLACK "\033[40m"
#define BG_RED   "\033[41m"
#define BG_GREEN "\033[42m"
#define BG_YELLOW "\033[43m"
#define BG_BLUE   "\033[44m"
#define BG_MAGENTA "\033[45m"
#define BG_CYAN    "\033[46m"
#define BG_WHITE   "\033[47m"

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
void relocatePatient(unordered_map<string, unique_ptr<Hospital>>& hospitals);
void dischargePatient(unordered_map<string, unique_ptr<Hospital>>& hospitals);
void requestMedication(unordered_map<string, unique_ptr<Hospital>>& hospitals, 
                      unordered_map<string, unique_ptr<Pharmacy>>& pharmacies);
void addPatient(unordered_map<string, unique_ptr<Hospital>>& hospitals);
void showLoadingAnimation(const string& message, int milliseconds = 1500);
string getHospitalByNumber(const unordered_map<string, unique_ptr<Hospital>>& hospitals);
string createHeader(const string& title);

int main() {
    cout << fixed << setprecision(2);
    
    // Clear screen
    system("clear");
    
    // Display welcome screen
    cout << BOLD << CYAN;
    cout << R"(
  ┌────────────────────────────────────────────────┐
  │     _    _                  _ _        _       │
  │    | |  | |                (_) |      | |      │
  │    | |__| | ___  ___ _ __   _| |_ __ _| |      │
  │    |  __  |/ _ \/ __| '_ \ | | __/ _` | |      │
  │    | |  | | (_) \__ \ |_) || | || (_| | |      │
  │    |_|  |_|\___/|___/ .__/_/ |\__\__,_|_|      │
  │         MANAGEMENT  | |                        │
  │            SYSTEM   |_|                        │
  └────────────────────────────────────────────────┘
)" << RESET << endl;

    cout << YELLOW << " Loading system components";
    for (int i = 0; i < 3; i++) {
        cout << ".";
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(300));
    }
    cout << GREEN << " Done!" << RESET << endl;
    
    bool runTests = false; // Set to true if you want to run tests
    
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
        auto primary = morks->getPatientById(1060)->getPrimaryDoctor();
        cout << primary->getName() << endl;
        morks->transferPatient(*ryans, 1060);
        cout << ryans->getPatientById(1060)->getPrimaryDoctor()->getName() << endl;
        assert(primary != ryans->getPatientById(1060)->getPrimaryDoctor());
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
        
        // Check if input is a number
        if (!(cin >> choice)) {
            // Input was not a number
            cin.clear();  // Clear error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard input
            cout << RED << "❌ Please enter a number from 1-7!" << RESET << endl;
            continue;  // Restart the loop
        }
        
        // Discard remaining input in buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1) {
            viewHospitals(hospitals);  
        }
        else if (choice == 2) {
            viewPatients(hospitals);  
        }
        else if (choice == 3) {
            relocatePatient(hospitals);
        }
        else if (choice == 4) {
            dischargePatient(hospitals);
        }
        else if (choice == 5) {
            requestMedication(hospitals, pharmacies);
        }
        else if (choice == 6) {
            addPatient(hospitals);
        }
        else if (choice == 7) {
            break;  
        }
        else {
            cout << RED << "❌ Invalid choice! Please enter a number from 1 to 7." << RESET << endl;
        }
    }

    cout << RED << "\nThank you for using the Hospital Management System!" << RESET << endl;
    return 0;
}

//Create hospital headers with frame dynamically
string createHeader(const string& title) {
    string result = "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n";
    result += "┃  🏥 " + title + string(38 - title.length(), ' ') + "┃\n";
    result += "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛";
    return result;
}

//Display the main menu
void displayMainMenu() {
    cout << BOLD << CYAN << "\n╔════════════════════════════════════════╗" << RESET << endl;
    cout << BOLD << CYAN << "║       🏥 HOSPITAL MANAGEMENT SYSTEM    ║" << RESET << endl;
    cout << BOLD << CYAN << "╚════════════════════════════════════════╝" << RESET << endl;
    
    cout << YELLOW << " 1. " << GREEN << "View Hospitals" << RESET << endl;
    cout << YELLOW << " 2. " << GREEN << "View Patients" << RESET << endl;
    cout << YELLOW << " 3. " << GREEN << "Relocate Patient" << RESET << endl;
    cout << YELLOW << " 4. " << GREEN << "Discharge Patient" << RESET << endl;
    cout << YELLOW << " 5. " << GREEN << "Request Medication" << RESET << endl;
    cout << YELLOW << " 6. " << GREEN << "Add Patient" << RESET << endl;
    cout << YELLOW << " 7. " << RED << "Exit" << RESET << endl;
    cout << CYAN << "\n Enter your choice: " << RESET;
}

//View hospitals with submenu
void viewHospitals(const unordered_map<string, unique_ptr<Hospital>>& hospitals) {
    while (true) {
        cout << BOLD << CYAN << "\n╔════════════════════════════════════════╗" << RESET << endl;
        cout << BOLD << CYAN << "║              🏥 HOSPITALS              ║" << RESET << endl;
        cout << BOLD << CYAN << "╚════════════════════════════════════════╝" << RESET << endl;

        // List hospitals with numbers
        vector<string> hospitalNames;
        int i = 1;
        for (const auto& [name, _] : hospitals) {
            hospitalNames.push_back(name);
            cout << CYAN << " " << i++ << ". " << WHITE << name << RESET << endl;
        }
        
        cout << CYAN << " " << i << ". " << YELLOW << "Return to Main Menu" << RESET << endl;
        
        // Get hospital selection
        int selection;
        cout << YELLOW << "\nSelect an option (1-" << i << "): " << RESET;
        
        if (!(cin >> selection)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << RED << "❌ Please enter a valid number!" << RESET << endl;
            continue;
        }
        
        // Return to main menu if user selected the last option
        if (selection == i) {
            return;
        }
        
        // Validate hospital selection
        if (selection < 1 || size_t(selection) > hospitalNames.size()) {
            cout << RED << "❌ Invalid hospital number!" << RESET << endl;
            continue;
        }
        
        string selectedHospital = hospitalNames[selection - 1];
        
        // Submenu for the selected hospital
        bool stayInSubmenu = true;
        while (stayInSubmenu) {
            
            // Using new createHeader function to generate dynamic hospital frame
            cout << BOLD << CYAN << createHeader(selectedHospital) << RESET << endl;
            
            cout << YELLOW << " 1. " << GREEN << "View Doctors" << RESET << endl;
            cout << YELLOW << " 2. " << GREEN << "View Nurses" << RESET << endl;
            cout << YELLOW << " 3. " << GREEN << "View Patients" << RESET << endl;
            cout << YELLOW << " 4. " << YELLOW << "Back to Hospital List" << RESET << endl;
            
            int subChoice;
            cout << YELLOW << "\nEnter your choice (1-4): " << RESET;
            
            if (!(cin >> subChoice)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << RED << "❌ Please enter a valid number!" << RESET << endl;
                continue;
            }
            
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            switch (subChoice) {
                case 1:
                    cout << BOLD << CYAN << "\n╔════════════════════════════════════════╗" << RESET << endl;
                    cout << BOLD << CYAN << "║          🩺 HOSPITAL DOCTORS           ║" << RESET << endl;
                    cout << BOLD << CYAN << "╚════════════════════════════════════════╝" << RESET << endl;
                    hospitals.at(selectedHospital)->printDoctors();
                    break;
                    
                case 2:
                    cout << BOLD << CYAN << "\n╔════════════════════════════════════════╗" << RESET << endl;
                    cout << BOLD << CYAN << "║          👩‍⚕️ HOSPITAL NURSES            ║" << RESET << endl;
                    cout << BOLD << CYAN << "╚════════════════════════════════════════╝" << RESET << endl;
                    hospitals.at(selectedHospital)->printNurses();
                    break;
                    
                case 3:
                    cout << BOLD << CYAN << "\n╔════════════════════════════════════════╗" << RESET << endl;
                    cout << BOLD << CYAN << "║         🛌 HOSPITAL PATIENTS           ║" << RESET << endl;
                    cout << BOLD << CYAN << "╚════════════════════════════════════════╝" << RESET << endl;
                    hospitals.at(selectedHospital)->printPatients();
                    break;
                    
                case 4:
                    // Back to hospital list
                    stayInSubmenu = false;
                    break;
                    
                default:
                    cout << RED << "❌ Invalid option! Please enter a number from 1 to 4." << RESET << endl;
            }
            
            if (stayInSubmenu && subChoice >= 1 && subChoice <= 3) {
                cout << YELLOW << "\nPress Enter to continue..." << RESET;
                cin.get();
            }
        }
    }
}

//View/search for patients
void viewPatients(const unordered_map<string, unique_ptr<Hospital>>& hospitals) {
    cout << BOLD << CYAN << "\n╔════════════════════════════════════════╗" << RESET << endl;
    cout << BOLD << CYAN << "║            👤 PATIENT LOOKUP           ║" << RESET << endl;
    cout << BOLD << CYAN << "╚════════════════════════════════════════╝" << RESET << endl;
    
    int patientID;
    cout << YELLOW << "Enter Patient ID to view details: " << RESET;
    cin >> patientID;

    // Search for the patient in each hospital
    bool found = false;
    for (const auto& [name, hospital] : hospitals) {
        Patient* patient = hospital->getPatientById(patientID);
        if (patient) {
            cout << GREEN << "\n✓ Patient with ID " << WHITE << BOLD << patientID 
                 << RESET << GREEN << " found in " << WHITE << BOLD << name << RESET << endl;
            
            // Create a visual box for patient info
            cout << BLUE << string(50, '-') << RESET << endl;
            patient->displayInfo();
            cout << BLUE << string(50, '-') << RESET << endl;
            found = true;
            break;
        }
    }
    
    if (!found) {
        cout << RED << "\n❌ Patient with ID " << patientID << " not found in any hospital!" << RESET << endl;
    }
}

// Get a hospital by number selection
string getHospitalByNumber(const unordered_map<string, unique_ptr<Hospital>>& hospitals) {
    // Display all hospitals with numbers
    cout << YELLOW << "Available Hospitals:" << RESET << endl;
    vector<string> hospitalNames;
    int i = 1;
    
    for (const auto& [name, _] : hospitals) {
        hospitalNames.push_back(name);
        cout << CYAN << " " << i++ << ". " << WHITE << name << RESET << endl;
    }
    
    // Get hospital selection
    int selection = 0;
    cout << YELLOW << "Enter hospital number: " << RESET;
    cin >> selection;
    
    // Validate selection
    if (selection < 1 || size_t(selection) > hospitalNames.size()) {
        cout << RED << "❌ Invalid hospital number!" << RESET << endl;
        return "";
    }
    
    // Return the selected hospital name
    return hospitalNames[selection - 1];
}

// Relocate a patient between hospitals
void relocatePatient(unordered_map<string, unique_ptr<Hospital>>& hospitals) {
    cout << BOLD << CYAN << "\n╔════════════════════════════════════════╗" << RESET << endl;
    cout << BOLD << CYAN << "║          🚑 RELOCATE PATIENT           ║" << RESET << endl;
    cout << BOLD << CYAN << "╚════════════════════════════════════════╝" << RESET << endl;
    
    // Get source hospital by number
    cout << YELLOW << "Select the patient's current hospital:" << RESET << endl;
    string sourceHospital = getHospitalByNumber(hospitals);
    if (sourceHospital.empty()) return;
    
    int patientID;
    cout << YELLOW << "Enter the Patient ID to relocate: " << RESET;
    cin >> patientID;
    
    Patient* patient = hospitals[sourceHospital]->getPatientById(patientID);
    if (!patient) {
        cout << RED << "❌ Patient not found in " << WHITE << BOLD << sourceHospital << RESET << RED << "!" << RESET << endl;
        return;
    }
    
    // Get destination hospital
    cin.ignore();
    cout << YELLOW << "Select the destination hospital:" << RESET << endl;
    string destHospital = getHospitalByNumber(hospitals);
    if (destHospital.empty()) return;
    
    if (sourceHospital == destHospital) {
        cout << RED << "❌ Source and destination hospitals cannot be the same!" << RESET << endl;
        return;
    }
    
    // Relocate patient
    hospitals[sourceHospital]->transferPatient(*hospitals[destHospital], patientID);
    cout << GREEN << "\n✓ Patient " << WHITE << BOLD << patientID << RESET << GREEN 
         << " successfully relocated from " << WHITE << BOLD << sourceHospital 
         << RESET << GREEN << " to " << WHITE << BOLD << destHospital << RESET << endl;
}

// Discharge a patient
void dischargePatient(unordered_map<string, unique_ptr<Hospital>>& hospitals) {
    cout << BOLD << CYAN << "\n╔════════════════════════════════════════╗" << RESET << endl;
    cout << BOLD << CYAN << "║           🏥 DISCHARGE PATIENT          ║" << RESET << endl;
    cout << BOLD << CYAN << "╚════════════════════════════════════════╝" << RESET << endl;
    
    int patientID;
    cout << YELLOW << "Enter Patient ID to discharge: " << RESET;
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
                cout << GREEN << "\n✓ Patient " << WHITE << BOLD << patientID << RESET << GREEN 
                     << " discharged by Dr. " << WHITE << BOLD << doctor->getName() << RESET << endl;
            } else {
                cout << RED << "❌ Patient has no primary doctor assigned!" << RESET << endl;
            }
            break;
        }
    }
    
    if (!found) {
        cout << RED << "❌ Patient with ID " << patientID << " not found in any hospital!" << RESET << endl;
    }
}

// Request medication from a pharmacy
void requestMedication(unordered_map<string, unique_ptr<Hospital>>& hospitals, 
                      unordered_map<string, unique_ptr<Pharmacy>>& pharmacies) {
    cout << BOLD << CYAN << "\n╔════════════════════════════════════════╗" << RESET << endl;
    cout << BOLD << CYAN << "║          💊 REQUEST MEDICATION         ║" << RESET << endl;
    cout << BOLD << CYAN << "╚════════════════════════════════════════╝" << RESET << endl;
    
    // Get hospital by number
    string hospitalName = getHospitalByNumber(hospitals);
    if (hospitalName.empty()) return;
    
    // Display all pharmacies with numbers
    cout << YELLOW << "Available Pharmacies:" << RESET << endl;
    vector<string> pharmacyNames;
    int i = 1;
    
    for (const auto& [name, _] : pharmacies) {
        pharmacyNames.push_back(name);
        cout << CYAN << " " << i++ << ". " << WHITE << name << RESET << endl;
    }
    
    // Get pharmacy selection
    int selection = 0;
    cout << YELLOW << "Enter pharmacy number: " << RESET;
    cin >> selection;
    
    // Validate selection
    if (selection < 1 || size_t(selection) > pharmacyNames.size()) {
        cout << RED << "❌ Invalid pharmacy number!" << RESET << endl;
        return;
    }
    
    string pharmacyName = pharmacyNames[selection - 1];
    
    // Ask for medication name
    string medicationName;
    cout << YELLOW << "Enter medication name: " << RESET;
    cin.ignore(); // Clear buffer before getting medication name
    getline(cin, medicationName);
    
    // Ask for quantity
    int quantity;
    cout << YELLOW << "Enter quantity: " << RESET;
    cin >> quantity;
    
    showLoadingAnimation("Processing medication request ");
    
    // Request medication
    double cost = pharmacies[pharmacyName]->requestMedication(*hospitals[hospitalName], medicationName, quantity);
    if (cost > 0) {
        cout << GREEN << "\n✓ Medication request successful. Total cost: " << WHITE << BOLD 
             << "$" << cost << RESET << GREEN << " billed to " << WHITE << BOLD 
             << hospitalName << RESET << endl;
    } else {
        cout << RED << "❌ Medication request failed!" << RESET << endl;
    }
}

// Add a new patient
void addPatient(unordered_map<string, unique_ptr<Hospital>>& hospitals) {
    cout << BOLD << CYAN << "\n╔════════════════════════════════════════╗" << RESET << endl;
    cout << BOLD << CYAN << "║           👤 ADD NEW PATIENT           ║" << RESET << endl;
    cout << BOLD << CYAN << "╚════════════════════════════════════════╝" << RESET << endl;
    
    // Get hospital by number
    string hospitalName = getHospitalByNumber(hospitals);
    if (hospitalName.empty()) return;
    
    // Clear input buffer after numeric input
    cin.ignore();
    
    // Get patient information
    string name, phoneNumber, condition, treatment;
    int year, month, day;
    
    cout << YELLOW << "Enter patient's name: " << RESET;
    getline(cin, name);
    
    cout << YELLOW << "Enter patient's phone number: " << RESET;
    getline(cin, phoneNumber);
    
    cout << YELLOW << "Enter patient's birth year (YYYY): " << RESET;
    cin >> year;
    cout << YELLOW << "Enter patient's birth month (1-12): " << RESET;
    cin >> month;
    cout << YELLOW << "Enter patient's birth day (1-31): " << RESET;
    cin >> day;
    
    cin.ignore(); // Clear the input buffer
    
    cout << YELLOW << "Enter patient's medical condition: " << RESET;
    getline(cin, condition);
    
    cout << YELLOW << "Enter patient's treatment plan: " << RESET;
    getline(cin, treatment);
    
    // Create the patient
    try {
        Date dob(year, month, day);
        
        // Check if hospital has capacity
        if (hospitals[hospitalName]->getNumAdmittedPatients() >= 20) {
            cout << RED << "❌ Hospital is at capacity. Cannot admit more patients." << RESET << endl;
            return;
        }
        
        showLoadingAnimation("Processing admission ");
        
        // Create and admit the patient
        hospitals[hospitalName]->admitPatient(make_unique<Patient>(
            name, phoneNumber, dob, condition, treatment
        ));
        
        cout << GREEN << "\n✓ Patient " << WHITE << BOLD << name << RESET << GREEN 
             << " successfully admitted to " << WHITE << BOLD << hospitalName << RESET << endl;
    } 
    catch (const exception& e) {
        cout << RED << "❌ Error: " << e.what() << RESET << endl;
    }
}

// Loading animation
void showLoadingAnimation(const string& message, int milliseconds) {
    cout << YELLOW << message;
    cout.flush();
    
    string spinner = "-\\|/";
    int iterations = milliseconds / 100;
    
    for (int i = 0; i < iterations; i++) {
        cout << BOLD << RED << spinner[i % spinner.length()] << "\b" << RESET;
        cout.flush();
        
        // Sleep for a fraction of a second
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    
    cout << GREEN << "✓" << RESET << endl;
}

