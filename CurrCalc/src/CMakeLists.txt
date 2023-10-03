project(CurrCalc_Application)

set(SOURCES 
    calculator/calculator.cpp
)

include(FetchContent)
FetchContent_Declare(
    cpr
    GIT_REPOSITORY https://github.com/libcpr/cpr.git
    GIT_TAG 1.10.4
) # Find the latest release here https://github.com/libcpr/cpr/releases
FetchContent_MakeAvailable(cpr)

add_library(CurrCalc_Lib STATIC ${SOURCES})
target_include_directories(CurrCalc_Lib PUBLIC include)

add_executable(CurrCalc_Application main.cpp)
target_link_libraries(CurrCalc_Application CurrCalc_Lib)