project(CurrCalc_Application)

set(SOURCES 
    calculator/calculator.cpp
    exchangerates_api_client/exchangerates_api_client.cpp
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
target_link_libraries(CurrCalc_Lib cpr::cpr)

add_executable(CurrCalc_Application main.cpp)
target_link_libraries(CurrCalc_Application CurrCalc_Lib)

if (WIN32)
    add_custom_command(
        TARGET CurrCalc_Application POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_RUNTIME_DLLS:CurrCalc_Application> $<TARGET_FILE_DIR:CurrCalc_Application>
        COMMAND_EXPAND_LISTS
    )
endif ()