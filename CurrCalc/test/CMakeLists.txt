project(CurrCalc_Test)

# Fetch the GTest library from GitHub and make it available as a library for the project
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
) # Find the latest release here https://github.com/google/googletest/releases
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE) # https://github.com/google/googletest/blob/main/googletest/README.md#visual-studio-dynamic-vs-static-runtimes
FetchContent_MakeAvailable(googletest)

# Set the source files that should be part of the CurrCalc test project
set(SOURCES 
    calculator/calculator_test.cpp
)

# Then the CurrCalc test application is created, and gtest and the CurrCalc lib are linked to it
add_executable(CurrCalc_Test ${SOURCES})
target_link_libraries(CurrCalc_Test PUBLIC gtest_main CurrCalc_Lib)

# Apparently it is not enough to link libraries to executables, as they are not included in the execution directories by CMake
# This custom command makes sure that the runtime dlls are copied into the execution directoreis after the build has completed
# For reference, check: https://discourse.cmake.org/t/usage-of-target-runtime-dlls-generator-expression/6355
if (CMAKE_IMPORT_LIBRARY_SUFFIX)
    add_custom_command(
        TARGET CurrCalc_Test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_RUNTIME_DLLS:CurrCalc_Test> $<TARGET_FILE_DIR:CurrCalc_Test>
        COMMAND_EXPAND_LISTS
    )
endif ()

# This registers the test project with CTest 
add_test(CurrCalc_Test CurrCalc_Test)