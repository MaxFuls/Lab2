cmake_minimum_required(VERSION 3.16)

find_package(Catch2 2 REQUIRED)

project(Lab2)

set(CMAKE_CXX_STANDART_20)

set(SMAKE_CXX_FLAGS "{CMAKE_CXX_FLAGS} -Wall -Wextra")

add_compile_options(-fprofile-arcs -ftest-coverage)

link_libraries(gcov)

add_library(Terminal src/Terminal/Terminal.cpp)

add_library(LogicElement src/LogicElement/LogicElement.cpp)

add_library(Dialog src/Dialog/Dialog.cpp) 

add_executable(Tests src/Tests/Tests.cpp)

add_executable(Lab2 src/Main.cpp)

target_link_libraries(Tests Terminal LogicElement Catch2::Catch2)

target_link_libraries(Terminal
    PRIVATE Dialog)

target_link_libraries(LogicElement
    PRIVATE Dialog
    PUBLIC Terminal)

target_link_libraries(Dialog
    PUBLIC Terminal
    PUBLIC LogicElement)

target_link_libraries(Lab2 Terminal LogicElement Dialog)
