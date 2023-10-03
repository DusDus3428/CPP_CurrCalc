cmake_minimum_required(VERSION 3.27.6)

project(CurrCalc)

# Set the C++ language standard for the project and make sure the the extensions are turned off
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable testing via CTest
enable_testing()

# Add the subdirectories for the CurrCalc application and test project
add_subdirectory(src)
add_subdirectory(test)