#include "Setup.hpp"
#include <iostream>

unordered_map<string, unique_ptr<Hospital>> setupHospitals() {
    unordered_map<string, unique_ptr<Hospital>> hospitals;
    
    hospitals["HotelDieu"] = make_unique<Hospital>("Hotel Dieu");
    hospitals["Met"] = make_unique<Hospital>("Met");
    hospitals["Mork's"] = make_unique<Hospital>("Mork's Sick Person Emporium and Grill");
    hospitals["Ryan's"] = make_unique<Hospital>("Ryan's Discotech Clinic");
    hospitals["Markos'"] = make_unique<Hospital>("Markos' Underground Chop Shop");

    vector<string> doctorNames = {
        "Mark Finerty", "Tamara Englbrecht", "Gwegg Duguay", "Dan Popescu", "Ryan Bluteau",
        "Sophia White", "James Adams", "Linda Carter", "Michael Trent", "Sarah Gibson",
        "Ethan Clark", "Olivia Martinez", "Noah Wilson", "Emma Thompson", "William Lee"
    };

    vector<string> nurseNames = {
        "Lisa Jones", "Brenda Smith", "Tom Hardy", "Judas Priest", "Aloy the Dog",
        "Nancy Drew", "Martha Kent", "Henry Cavill", "Eliza Thornberry", "Clark Kent",
        "Dwayne Johnson", "Samantha Green", "Jake Peralta", "Rosie Diaz", "Charles Boyle",
        "Amy Santiago", "Terry Jeffords", "Captain Holt", "Hitchcock", "Scully"
    };

    vector<string> patientNames = {
        "John Doe", "Mork Fin", "Alice Brown", "David Smith", "Sophia Wilson",
        "Liam Johnson", "Olivia Davis", "Noah Martinez", "Emma Garcia", "William Lee",
        "James O'Connell", "Rachel Green", "Monica Geller", "Joey Tribbiani", "Ross Geller",
        "Chandler Bing", "Phoebe Buffay", "Ted Mosby", "Barney Stinson", "Marshall Eriksen"
    };

    vector<string> conditions = {
        "Flu", "Tinnitus", "Asthma", "Diabetes", "Hypertension",
        "Fractured Arm", "Migraine", "Pneumonia", "Allergic Reaction", "COVID-19"
    };

    vector<string> treatments = {
        "Intravenous Fluids", "Music Therapy", "Inhaler & Oxygen Therapy", 
        "Insulin & Diet Control", "Blood Pressure Medication",
        "Casting & Pain Management", "Pain Relief & Hydration Therapy",
        "Antibiotics & Ventilation", "Antihistamines & EpiPen", "Oxygen Therapy & Antiviral Drugs"
    };

    size_t docIndex = 0, nurseIndex = 0, patientIndex = 0;

    for (auto& [key, hospital] : hospitals) {
        // **Add 3 doctors per hospital**
        for (int j = 0; j < 3; j++, docIndex++) {
            if (docIndex >= doctorNames.size()) docIndex = 0; // Loop around if out of names
            hospital->addDoctor(make_unique<Doctor>(
                doctorNames[docIndex], 
                Date(1970 + (docIndex % 30), (docIndex % 12) + 1, (docIndex % 28) + 1), 
                "123456789",
                hospital.get() // Pass hospital pointer to Doctor constructor
            ));
        }

        // **Add 5 nurses per hospital**
        for (int j = 0; j < 5; j++, nurseIndex++) {
            if (nurseIndex >= nurseNames.size()) nurseIndex = 0; // Loop around
            hospital->addNurse(make_unique<Nurse>(
                nurseNames[nurseIndex], 
                Date(1970 + (nurseIndex % 30), (nurseIndex % 12) + 1, (nurseIndex % 28) + 1), 
                "987654321",
                hospital.get() // Pass hospital pointer to Nurse constructor
            ));
        }

        // **Admit 10 patients per hospital**
        for (int j = 0; j < 10; j++, patientIndex++) {
            if (patientIndex >= patientNames.size()) patientIndex = 0; // Loop around
            int conditionIndex = patientIndex % conditions.size();

            hospital->admitPatient(make_unique<Patient>(
                patientNames[patientIndex], 
                "519" + to_string(9000000 + patientIndex), 
                Date(1970 + (patientIndex % 30), (patientIndex % 12) + 1, (patientIndex % 28) + 1),
                conditions[conditionIndex], 
                treatments[conditionIndex]
            ));
        }
    }

    cout << "Setup complete! Each hospital has 3 doctors, 5 nurses, and 10 patients.\n";
    return hospitals;
}
