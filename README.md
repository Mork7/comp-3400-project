# COMP-3400 - Hospital Management System

## Supervisor
- Dr. Ryan Bluteau

## Members
- Mark Finerty
- Markos Mora Naranjo
- Trina Des

## Project Description
This project implements a Hospital Management System using C++. It manages patient admissions, doctors, nurses, pharmacies, and hospital locations. The system keeps track of patient stays and billing based on the duration of hospitalization.

## Project Structure
```
/hospital-management/
│── 📂 src/                # Source code files
│    ├── Date.cpp          # Date class implementation
│    ├── Patient.cpp       # Patient class implementation
│    ├── main.cpp          # Entry point of the program
│
│── 📂 include/            # Header files
│    ├── Date.hpp          # Date class header
│    ├── Patient.hpp       # Patient class header
│
│── 📂 build/              # Compiled object files (.o) and executable
│
│── Makefile               # Automates the build process
│── README.md              # Documentation on how to run the project
│── .gitignore             # Ignore compiled files, object files, etc.
```

## How to Build and Run

### **1️⃣ Install Dependencies**
Ensure you have `g++` installed (GCC compiler for C++).

```sh
sudo apt update && sudo apt install g++
```

### **2️⃣ Build the Project**
Run the following command to compile the project:
```sh
make
```
This will compile all source files and generate an executable inside the `build/` directory.

### **3️⃣ Run the Executable**
```sh
./build/hospital_system
```

### **4️⃣ Clean Compiled Files**
To remove compiled files and reset the build:
```sh
make clean
```

## Git Best Practices
Before committing, ensure you **do not** push compiled files. Use `.gitignore` to ignore unnecessary files:
```
# Ignore compiled files
/build/
*.o
*.out
*.exe
```

## Notes
- Ensure all `.cpp` files are placed inside `src/` and `.hpp` files inside `include/`.
- If you face permission issues when running `./build/hospital_system`, make sure it has execute permissions:
  ```sh
  chmod +x ./build/hospital_system
  ```
---