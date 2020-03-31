# Log Health utility build script
# @author Maxim Menshikov (info@menshikov.org)
cmake_minimum_required(VERSION 3.0)

project(loghealth)

option(LOGHEALTH_ENABLE_CLANG_TIDY "Enable loghealth clang-tidy" OFF)

set(SRC src/main.cpp
        src/LogSummary.cpp
        src/LogSummaryPoint.cpp
        src/LogTimeSpan.cpp
        src/LogUtility.cpp)

add_executable(${PROJECT_NAME} ${SRC})
target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} stdc++fs)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

if (LOGHEALTH_ENABLE_CLANG_TIDY)
    find_program(CLANG_TIDY_BINARY NAMES "clang-tidy")
    if (CLANG_TIDY_BINARY)
        set_target_properties(${PROJECT_NAME} PROPERTIES
                              CXX_CLANG_TIDY "${CLANG_TIDY_BINARY}")
    else ()
        message(STATUS "clang-tidy not found")
    endif()
endif()
