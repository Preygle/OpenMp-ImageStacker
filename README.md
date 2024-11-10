Project Name
This project demonstrates how to set up and build a C++ project using CMake on Windows.

Prerequisites
CMake: Download and install CMake from here.
C++ Compiler: Ensure you have a C++ compiler, such as Visual Studio with C++ support.
Steps to Build the Project

1. Install CMake
Download and install CMake from CMake Downloads.

2. Create a Build Directory
Open Command Prompt, navigate to your project directory, and create a build folder:
mkdir build

3. Generate Build Files
Run the following command to generate the build files in the build directory:
cmake -B .\build\

4. Build the Project
To compile the project, run:
cmake --build .\build\

5. Run the Executable
Once built, run the executable:
.\build\Debug\cpp.exe

Directory Structure
/your_project
    /src
        - main.cpp
    /build
    CMakeLists.txt
    README.md


