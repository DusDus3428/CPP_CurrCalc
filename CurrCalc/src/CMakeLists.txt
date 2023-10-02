set(SOURCES 
    calculator/Calculator.cpp
)
set(HEADERS 
    calculator/Calculator.h
)

include(FetchContent)
FetchContent_Declare(
    cpr
    GIT_REPOSITORY https://github.com/libcpr/cpr.git
    GIT_TAG 1.10.4
) # Find the latest release here https://github.com/libcpr/cpr/releases
FetchContent_MakeAvailable(cpr)

add_library(CurrCalc_Lib_For_Tests STATIC ${SOURCES} ${HEADERS})

add_executable(CurrCalc_Application main.cpp)
target_link_libraries(CurrCalc_Application CurrCalc_Lib_For_Tests)