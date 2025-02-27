#include "Date.hpp"
#include "Patient.hpp"
#include "Hospital.hpp"
#include <memory>

using namespace std;

int main(){
    auto p1 = make_unique<Patient>("John Doe","5199353845", Date(1995,7,16), "Flu", "Intravenis Fluids");
    auto p2 = make_unique<Patient>("Mork Fin","5199284721", Date(1992,07,21), "Tinnitus", "Music Therapy");

    Hospital hospital1("Hotel Dieu");
    hospital1.addPatient(move(p1));
    hospital1.addPatient(move(p2));
    hospital1.printPatients();

}