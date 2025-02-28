#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <memory>
#include <vector>
#include <string>
#include <Nurse.hpp>
#include <Doctor.hpp>
#include <Patient.hpp>

class Hospital {
    private:
        std::string name;
        std::vector<std::unique_ptr<Nurse>> nurses;
        std::vector<std::unique_ptr<Doctor>> doctors;
        std::vector<std::unique_ptr<Patient>> patients;
        int numAdmittedPatients;
        double funds;
        void dischargePatientFromHospital(int patientID);
        
        public:
        Hospital(std::string name);
        void addDoctor(std::unique_ptr<Doctor> doctor);
        void addNurse(std::unique_ptr<Nurse> nurse);
        void admitPatient(std::unique_ptr<Patient> patient);
        std::string getName();
        void printPatients();
        void printDoctors();
        void printNurses();
        void transferPatient(Hospital& newHospital, int patientID);
        void payPharmacy(double amount);
        int getNumAdmittedPatients() const;
        double getFunds() const;
        Doctor* getDoctorById(int doctorID);
        Patient* getPatientById(int patientID);
        Nurse* getNurseById(int nurseID);
        std::vector<std::unique_ptr<Nurse>>& getNurses(); 
        std::vector<std::unique_ptr<Doctor>>& getDoctors();
        std::vector<std::unique_ptr<Patient>>& getPatients();

    friend class Doctor; // this will allow Doctor to call the dischargeFromHospital() method in hospital.
};
#endif