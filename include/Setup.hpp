#ifndef SETUP_HPP
#define SETUP_HPP

#include <vector>
#include <unordered_map>
#include <memory>
#include <string>
#include "Hospital.hpp"
#include "Doctor.hpp"
#include "Nurse.hpp"
#include "Patient.hpp"

using namespace std;

// Function to initialize hospitals, doctors, nurses, and patients
unordered_map<string, unique_ptr<Hospital>> setupHospitals();

#endif
