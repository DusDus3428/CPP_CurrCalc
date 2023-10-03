project(CurrCalc_Test)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
) # Find the latest release here https://github.com/google/googletest/releases
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(SOURCES 
    calculator/calculator_test.cpp
)

add_executable(CurrCalc_Test ${SOURCES})

target_link_libraries(CurrCalc_Test PUBLIC
gtest_main
CurrCalc_Lib
)

if (WIN32)
    add_custom_command(
        TARGET CurrCalc_Test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_RUNTIME_DLLS:CurrCalc_Test> $<TARGET_FILE_DIR:CurrCalc_Test>
        COMMAND_EXPAND_LISTS
    )
endif ()

add_test(CurrCalc_Test CurrCalc_Test)