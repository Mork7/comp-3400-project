#include "Setup.hpp"
#include <iostream>

unordered_map<string, unique_ptr<Hospital>> setupHospitals() {
    unordered_map<string, unique_ptr<Hospital>> hospitals;
    
    hospitals["Mork's Sick Person Emporium and Grill"] = make_unique<Hospital>("Mork's Sick Person Emporium and Grill");
    hospitals["Ryan's Discotech Clinic"] = make_unique<Hospital>("Ryan's Discotech Clinic");
    hospitals["Hotel-Dieu Grace Healthcare"] = make_unique<Hospital>("Hotel-Dieu Grace Healthcare");
    hospitals["Windsor Regional Hospital Met Campus"] = make_unique<Hospital>("Windsor Regional Hospital Met Campus");
    hospitals["Markos' Underground Chop Shop"] = make_unique<Hospital>("Markos' Underground Chop Shop");

    vector<string> doctorNames = {
        "Mark Finerty", "Tamara Englbrecht", "Gwegg Duguay", "Dan Popescu", "Ryan Bluteau",
        "Sophia White", "James Adams", "Linda Carter", "Michael Trent", "Sarah Gibson",
        "Ethan Clark", "Olivia Martinez", "Noah Wilson", "Emma Thompson", "William Lee",
        "David Wallace", "Jack Harper", "Samantha Reid", "Richard Hammond", "Elon Stark",
        "Bruce Wayne", "Clark Kent", "Peter Parker", "Natasha Romanoff", "Tony Stark",
        "Stephen Strange", "Leonard McCoy", "Gregory House", "James Wilson", "Lisa Cuddy",
        "Derek Shepherd", "Meredith Grey", "Cristina Yang", "Mark Sloan", "Miranda Bailey",
        "Preston Burke", "Robert Chase", "Eric Foreman", "Allison Cameron", "Remy Hadley",
        "John Carter", "Doug Ross", "Benton Benton", "Elizabeth Corday", "Neela Rasgotra",
        "Abby Lockhart", "Luka Kovac", "George Clooney", "John Dorian", "Elliot Reid"
    };
    

    vector<string> nurseNames = {
        "Lisa Jones", "Brenda Smith", "Tom Hardy", "Judas Priest", "Aloy the Dog",
        "Nancy Drew", "Martha Kent", "Henry Cavill", "Eliza Thornberry", "Clark Kent",
        "Dwayne Johnson", "Samantha Green", "Jake Peralta", "Rosie Diaz", "Charles Boyle",
        "Amy Santiago", "Terry Jeffords", "Captain Holt", "Hitchcock", "Scully",
        "Florence Nightingale", "Clara Barton", "Mary Seacole", "Margaret Sanger",
        "Lillian Wald", "Dorothea Dix", "Virginia Henderson", "Linda Richards",
        "Madeleine Leininger", "Isabel Hampton", "Emily Stowe", "Jean Watson",
        "Elizabeth Blackwell", "Elizabeth Kenny", "Anna Maxwell", "Sally Louisa Tompkins",
        "Mary Todd Lincoln", "Louisa May Alcott", "Grace Darling", "Josephine Baker",
        "Beverly Crusher", "Christine Chapel", "Jackie Peyton", "Zoe Barnes", 
        "Carla Espinosa", "Sam Taggart", "Frank Burns", "Margaret Houlihan", 
        "Ann Perkins", "Leslie Knope"
    };
    

    vector<string> patientNames = {
        "John Doe", "Mork Fin", "Alice Brown", "David Smith", "Sophia Wilson",
        "Liam Johnson", "Olivia Davis", "Noah Martinez", "Emma Garcia", "William Lee",
        "James O'Connell", "Rachel Green", "Monica Geller", "Joey Tribbiani", "Ross Geller",
        "Chandler Bing", "Phoebe Buffay", "Ted Mosby", "Barney Stinson", "Marshall Eriksen",
        "Lily Aldrin", "Robin Scherbatsky", "Michael Scott", "Dwight Schrute", "Jim Halpert",
        "Pam Beesly", "Angela Martin", "Kevin Malone", "Oscar Martinez", "Stanley Hudson",
        "Creed Bratton", "Meredith Palmer", "Ryan Howard", "Kelly Kapoor", "Darryl Philbin",
        "Toby Flenderson", "Jan Levinson", "David Wallace", "Gabe Lewis", "Robert California",
        "Andy Bernard", "Erin Hannon", "Nellie Bertram", "Clark Green", "Pete Miller",
        "Holly Flax", "Todd Packer", "Karen Filippelli", "Charles Miner", "Deangelo Vickers",
        "Doug Judy", "Bill Lumbergh", "Peter Gibbons", "Samir Nagheenanajar", "Michael Bolton",
        "Milton Waddams", "Jennifer Aniston", "Tim Canterbury", "Dawn Tinsley", "Gareth Keenan",
        "Brent Wernick", "Lucy Whitmore", "Henry Roth", "Ula", "Doug Whitmore",
        "Tom Haverford", "April Ludgate", "Ron Swanson", "Donna Meagle", "Chris Traeger",
        "Ben Wyatt", "Jerry Gergich", "Ann Perkins", "Jean-Ralphio Saperstein",
        "Mona-Lisa Saperstein", "Burt Macklin", "Janet Snakehole", "Eleanor Shellstrop",
        "Chidi Anagonye", "Tahani Al-Jamil", "Jason Mendoza", "Michael", "Shawn",
        "Trevor", "Derek", "Janet", "Judge Gen", "Steve Harrington", "Dustin Henderson",
        "Lucas Sinclair", "Max Mayfield", "Will Byers", "Eleven", "Mike Wheeler",
        "Nancy Wheeler", "Jonathan Byers", "Joyce Byers", "Jim Hopper"
    };
    

    vector<string> conditions = {
        "Flu", "Tinnitus", "Asthma", "Diabetes", "Hypertension",
        "Fractured Arm", "Migraine", "Pneumonia", "Allergic Reaction", "COVID-19",
        "Appendicitis", "Bronchitis", "Chronic Fatigue Syndrome", "Concussion",
        "Epilepsy", "Food Poisoning", "Gastroenteritis", "Heart Attack",
        "Kidney Stones", "Strep Throat"
    };
    

    vector<string> treatments = {
        "Intravenous Fluids", "Music Therapy", "Inhaler & Oxygen Therapy", 
        "Insulin & Diet Control", "Blood Pressure Medication",
        "Casting & Pain Management", "Pain Relief & Hydration Therapy",
        "Antibiotics & Ventilation", "Antihistamines & EpiPen", "Oxygen Therapy & Antiviral Drugs",
        "Emergency Appendectomy", "Cough Syrup & Rest", "Cognitive Behavioral Therapy",
        "Observation & Pain Management", "Anticonvulsant Medication",
        "IV Fluids & Anti-Nausea Medication", "Oral Rehydration & Antacids",
        "CPR & Blood Thinners", "Pain Management & Hydration Therapy",
        "Antibiotics & Rest"
    };
    

    size_t docIndex = 0, nurseIndex = 0, patientIndex = 0;

    for (auto& [key, hospital] : hospitals) {
        // **Add 10 doctors per hospital**
        for (int j = 0; j < 10; j++, docIndex++) {
            if (docIndex >= doctorNames.size()) docIndex = 0; // Loop around if out of names
            hospital->addDoctor(make_unique<Doctor>(
                doctorNames[docIndex], 
                Date(1970 + (docIndex % 30), (docIndex % 12) + 1, (docIndex % 28) + 1), 
                "123456789",
                hospital.get() // Pass hospital pointer to Doctor constructor
            ));
        }

        // **Add 10 nurses per hospital**
        for (int j = 0; j < 10; j++, nurseIndex++) {
            if (nurseIndex >= nurseNames.size()) nurseIndex = 0; // Loop around
            hospital->addNurse(make_unique<Nurse>(
                nurseNames[nurseIndex], 
                Date(1970 + (nurseIndex % 30), (nurseIndex % 12) + 1, (nurseIndex % 28) + 1), 
                "987654321",
                hospital.get() // Pass hospital pointer to Nurse constructor
            ));
        }

        // **Admit 15 patients per hospital**
        for (int j = 0; j < 15; j++, patientIndex++) {
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

    cout << "Setup complete! Each hospital has 10 doctors, 10 nurses, and 15 patients.\n";
    return hospitals;
}

unordered_map<string, unique_ptr<Pharmacy>> setupPharmacies() {
    unordered_map<string, unique_ptr<Pharmacy>> pharmacies;

    vector<string> pharmacyNames = {
        "MediCorp", "HealthPlus", "PharmaCare", "Wellness Drugs", "LifeLine Pharmacy",
        "Rx Express", "CureWell", "Guardian Pharmacy", "PillPoint", "CareMed",
        "QuickMeds", "SafeDose", "MedLife", "TotalHealth", "HealthFirst",
        "VitalMeds", "WellRx", "CityCare Pharmacy", "PureHealth", "FastMeds"
    };

    for (size_t i = 0; i < pharmacyNames.size(); i++) {
        pharmacies[pharmacyNames[i]] = make_unique<Pharmacy>(i + 1, pharmacyNames[i]);

        // Add some medications
        pharmacies[pharmacyNames[i]]->addMedication("Paracetamol", 5.0);
        pharmacies[pharmacyNames[i]]->addMedication("Ibuprofen", 8.0);
        pharmacies[pharmacyNames[i]]->addMedication("Antibiotics", 15.0);
        pharmacies[pharmacyNames[i]]->addMedication("Cough Syrup", 12.0);
    }

    return pharmacies;
}