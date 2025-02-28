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
│── 📂 build/              # Compiled object files and executable (generated by CMake)
│
│── CMakeLists.txt         # CMake configuration for cross-platform builds
│── README.md              # Documentation on how to run the project
│── .gitignore             # Ignore compiled files, object files, etc.
```

---

## How to Build and Run

### **Linux/macOS Instructions**

#### **1️⃣ Install Dependencies**
Ensure you have `g++` and `cmake` installed.
```sh
sudo apt update && sudo apt install g++ cmake
```

#### **2️⃣ Build the Project Using CMake**
```sh
mkdir -p build
cd build
cmake ..
make
```
This will compile all source files and generate an executable inside the `build/` directory.

#### **3️⃣ Run the Executable**
```sh
./hospital_system
```

#### **4️⃣ Clean Compiled Files**
To remove compiled files, delete the `build/` directory:
```sh
rm -r build
```
or if still inside the `build/` directory:
```sh
rm -r *
```

---

### **Windows Instructions (Using CMake and MSVC/MinGW)**

#### **1️⃣ Install Dependencies**
Ensure you have a C++ compiler installed:
- **Option 1 (Recommended):** Install **Microsoft Visual Studio** with C++ development tools.
- **Option 2:** Install **MinGW** (if you prefer `g++` on Windows).
  - Download: [https://www.mingw-w64.org/](https://www.mingw-w64.org/)
  - Add MinGW to your `PATH` environment variable.

#### **2️⃣ Build Using CMake**
Open **PowerShell** or **Command Prompt** and run:
```sh
mkdir build
cd build
cmake ..
cmake --build . --config Debug
```
- If using MinGW, add `-G "MinGW Makefiles"` to the `cmake ..` command:
  ```sh
  cmake -G "MinGW Makefiles" ..
  cmake --build .
  ```

#### **3️⃣ Run the Executable**
After building, the executable will be inside the `build/` directory: 
```sh
.\hospital_system.exe
```

#### **4️⃣ Clean Compiled Files**
To remove compiled files, delete the `build/` directory:
```sh
rm -r build
```

---

## Git Best Practices
Before committing, ensure you **do not** push compiled files. Use `.gitignore` to ignore unnecessary files:
```
# Ignore compiled files
/build/
*.o
*.out
*.exe
CMakeCache.txt
CMakeFiles/
```

---

## Notes
- Ensure all `.cpp` files are placed inside `src/` and `.hpp` files inside `include/`.
- If you face **permission issues** when running `./hospital_system` on Linux/macOS, make sure it has execute permissions:
  ```sh
  chmod +x ./hospital_system
  ```
- If using **MinGW**, ensure `mingw32-make` is installed and added to your `PATH` before running CMake.

