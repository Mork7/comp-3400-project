#include <memory>
#include <vector>
#include "Employee.hpp"
#include "Patient.hpp"

class Hospital {
private:
    std::string name;
    std::vector<std::unique_ptr<Employee>> nurses;
    std::vector<std::unique_ptr<Employee>> doctors;
    std::vector<std::unique_ptr<Patient>> patients;

public:
    Hospital(std::string name);
    void addDoctor(std::unique_ptr<Employee> doctor);
    void addNurse(std::unique_ptr<Employee> nurse);
    void addPatient(std::unique_ptr<Patient> patient);
    std::string getName();
    void printPatients();
};
