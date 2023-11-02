find_package(Catch 2 REQUIRED)

add_executable(terminal_tests Tests.cpp)

target_link_libraries(terminal_test Terminal LogicElement Catch2::Catch2)