cmake_minimum_required(VERSION 3.27.6)

project(CurrCalc)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()

add_subdirectory(src)
add_subdirectory(test)