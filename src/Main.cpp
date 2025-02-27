#include "Setup.hpp"
#include <iostream>
#include <iomanip> 
#include <cassert>

using namespace std;

int main() {
    cout << fixed << setprecision(2);
    auto hospitals = setupHospitals();
    auto pharmacies = setupPharmacies();

    // Get two hospitals for testing
    Hospital* morks = hospitals["Mork's"].get();
    Hospital* ryans = hospitals["Ryan's"].get();
    assert(morks != nullptr && "Test failed: Mork's hospital not found!");
    assert(ryans != nullptr && "Test failed: Ryan's hospital not found!");

    // Initial fund checks
    double initialFundsMorks = morks->getFunds();  // Set your starting hospital funds
    double initialFundsRyans = ryans->getFunds();
    assert(morks->getFunds() == initialFundsMorks && "Test failed: Mork's initial funds incorrect!");
    assert(ryans->getFunds() == initialFundsRyans && "Test failed: Ryan's initial funds incorrect!");

    // Get a pharmacy
    Pharmacy* mediCorp = pharmacies["MediCorp"].get();
    assert(mediCorp != nullptr && "Test failed: MediCorp pharmacy not found!");

    mediCorp->listMedications();

    cout << "\nMork's Sick Person Emporium and Grill ordering Ibuprofen (10 units)...\n";
    double cost1 = mediCorp->requestMedication(*morks, "Ibuprofen", 10);
    assert(cost1 == 80.00 && "Test failed: Incorrect total cost for Ibuprofen!");
    assert(morks->getFunds() == initialFundsMorks - cost1 && "Test failed: Mork's funds did not decrease correctly!");

    cout << "\nRyan's Discotech Clinic ordering Antibiotics (5 units)...\n";
    double cost2 = mediCorp->requestMedication(*ryans, "Antibiotics", 5);
    assert(cost2 == 75.00 && "Test failed: Incorrect total cost for Antibiotics!");
    assert(ryans->getFunds() == initialFundsRyans - cost2 && "Test failed: Ryan's funds did not decrease correctly!");

    cout << "\nRyan's ordering Pecocet (5 units)... (Expected to fail)\n";
    double cost3 = mediCorp->requestMedication(*ryans, "Pecocet", 5);
    assert(cost3 == -1 && "Test failed: Invalid medication request should return -1!");
    assert(ryans->getFunds() == initialFundsRyans - cost2 && "Test failed: Ryan's funds should not change for invalid order!");

    cout << "\nAll assertions passed successfully.\n";

    return 0;
}
