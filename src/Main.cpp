#include "Date.hpp"
#include "Patient.hpp"

using namespace std;

int main(){

     
    Date discharge(2025, 2, 26);

    Patient p1("John Doe","5199353845", Date(1995,7,16), "Flu", "Intravenis Fluids");
    Patient p2("Mork Fin","5199034721", Date(1992,07,21), "Elephant Penis", "Penis reduction surgery");
    p1.discharge(discharge);
    p1.displayInfo();
    p2.displayInfo();

};