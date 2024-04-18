cmake_minimum_required(VERSION 3.26)
project(Prog3)

set(CMAKE_CXX_STANDARD 17)

add_executable(Prog3 main.cpp
        Window.cpp
        Window.h
        StateWindow.h
        StateWindow.cpp
        CSVParser.h
        CSVParser.cpp
        )

set(SFML_STATIC_LIBRARIES TRUE)
set(DCSV2_BUILD_TESTS TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/SFML/include/SFML
                C:/csv2/include/csv2)
target_link_libraries(Prog3 sfml-system sfml-window sfml-graphics sfml-audio)