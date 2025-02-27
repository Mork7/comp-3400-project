#ifndef PHARMACY_HPP
#define PHARMACY_HPP

#include <string>
#include <unordered_map>
#include <iostream>

class Hospital;

class Pharmacy {
private:
    static int nextID;
    int pharmacyID;
    std::string name;
    // we'll use a map to store names of meds and a price
    std::unordered_map<std::string, double> medicationPrices;

public:
    Pharmacy(int id, std::string name);
    void addMedication(std::string medName, double price);
    void listMedications() const;
    double requestMedication(Hospital& hospital, std::string medName, int quantity);
    int getID() const;
    std::string getName() const;
};

#endif
