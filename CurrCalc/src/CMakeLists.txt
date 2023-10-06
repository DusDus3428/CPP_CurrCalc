project(CurrCalc_Application)

# Fetch the CPR library from GitHub and make it available as a library for the project
include(FetchContent)
FetchContent_Declare(
    cpr
    GIT_REPOSITORY https://github.com/libcpr/cpr.git
    GIT_TAG 1.10.4
) # Find the latest release here https://github.com/libcpr/cpr/releases
FetchContent_MakeAvailable(cpr)
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.2
) # Find the latest release here https://github.com/libcpr/cpr/releases
FetchContent_MakeAvailable(nlohmann_json)

# Set the source files that should be part of the CurrCalc library
set(SOURCES 
    currency_detail/currency_detail.cpp
    exchange_rate/exchange_rate.cpp
    exchangerates_api_client/exchangerates_api_client.cpp
    util/input_output.cpp
)

# The main code will be built into a separate library, CurrCalc_Lib
# This library will then be linked to the CurrCalc_Application executable
# This is done so that the library code can be tested by linking it to the CurrCalc_Test project

# First, the Curr_Calc library should be created with the specified source files
# Then the header files, located within a separate include directory, will be included
# Then we link the CPR library becuase it will be used by the CurrCalc lib
add_library(CurrCalc_Lib STATIC ${SOURCES})
target_include_directories(CurrCalc_Lib PUBLIC include)
target_link_libraries(CurrCalc_Lib cpr::cpr nlohmann_json::nlohmann_json)

# Then the CurrCalc application is created and the CurrCalc lib is linked to it
add_executable(CurrCalc_Application main.cpp)
target_link_libraries(CurrCalc_Application CurrCalc_Lib)

# Apparently it is not enough to link libraries to executables, as they are not included in the execution directories by CMake
# This custom command makes sure that the runtime dlls are copied into the execution directoreis after the build has completed
# For reference, check: https://discourse.cmake.org/t/usage-of-target-runtime-dlls-generator-expression/6355
if (CMAKE_IMPORT_LIBRARY_SUFFIX)
    add_custom_command(
        TARGET CurrCalc_Application POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_RUNTIME_DLLS:CurrCalc_Application> $<TARGET_FILE_DIR:CurrCalc_Application>
        COMMAND_EXPAND_LISTS
    )
endif ()