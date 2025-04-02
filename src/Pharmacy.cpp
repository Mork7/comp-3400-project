#include "Pharmacy.hpp"
#include "Hospital.hpp"

using namespace std;

int Pharmacy::nextID = 1;

Pharmacy::Pharmacy(int id, string name) : pharmacyID(nextID++), name(name) {}

// Add a medication, might include in-stock amount but meh
void Pharmacy::addMedication(string medName, double price) {
    medicationPrices[medName] = price;
}

// List all meds the pharmacy has
void Pharmacy::listMedications() const {
    cout << "\033[32m" << name << "\033[0m - Available Medications:\n";
    for (const auto& med : medicationPrices) {
        cout << med.first << " - $" << med.second << " per unit\n";
    }
}

// Fulfill request from a hospital for drugs
double Pharmacy::requestMedication(Hospital& hospital, string medName, int quantity) {
    if (medicationPrices.find(medName) == medicationPrices.end()) {
        cerr << "\033[31mError:\033[0m Medication " << medName << " not available at " << name << ".\n";
        return -1;
    }

    double totalCost = medicationPrices[medName] * quantity;
    cout << "Hospital " << hospital.getName() << " ordered " << quantity
              << " units of " << medName << " from " << name << " for $" << totalCost << ".\n";
    
    hospital.payPharmacy(totalCost);

    return totalCost;
}

// GETTERS
// Get pharamacy id
int Pharmacy::getID() const { 
    return pharmacyID;
}
// Get name
string Pharmacy::getName() const { 
    return name; 
}
