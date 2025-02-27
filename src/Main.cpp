#include "Setup.hpp"
#include <iostream>

using namespace std;

int main() {
    auto hospitals = setupHospitals();
    Hospital* morks = hospitals["Mork's"].get();

    morks->printDoctors();
    morks->printNurses();
    morks->printPatients();

    morks->getDoctorById(17)->dischargePatient(1020);
    morks->getPatientById(1020)->displayInfo();
   
    return 0;
}
