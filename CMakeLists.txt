cmake_minimum_required(VERSION 3.22)

project(FL_module)

find_package(Qt5 REQUIRED COMPONENTS Widgets Gui)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_BUILD_TYPE "Debug")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                   ${CMAKE_CURRENT_SOURCE_DIR}/FLModule
                   ${CMAKE_CURRENT_SOURCE_DIR}/Kernel
                   ${CMAKE_CURRENT_SOURCE_DIR}/Keyboard
                   ${CMAKE_CURRENT_SOURCE_DIR}/Library)

file(GLOB SOURCES 
    FLModule/*.cpp 
    Kernel/*.cpp 
    Keyboard/*.cpp 
    Library/Observer2/*.cpp
)

file(GLOB HEADERS
    FLModule/*.h
    Kernel/*.h
    Keyboard/*.h
    Library/Observer2/*.h
)

add_executable(
    FL_module
    ${SOURCES}
    ${HEADERS}
)

target_link_libraries(FL_module Qt5::Widgets Qt5::Gui)

# Tests
find_package(Qt5 REQUIRED COMPONENTS Test)

add_executable(FL_module_tests
    Tests/TestFingerLayoutModule.cpp
    FLModule/FingerLayoutModule.cpp
    Kernel/FingerLayout.cpp
)

target_include_directories(FL_module_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/FLModule
    ${CMAKE_CURRENT_SOURCE_DIR}/Kernel
    ${CMAKE_CURRENT_SOURCE_DIR}/Keyboard
    ${CMAKE_CURRENT_SOURCE_DIR}/Library
)

target_link_libraries(FL_module_tests Qt5::Test)

enable_testing()
add_test(NAME FL_module_tests COMMAND FL_module_tests)
