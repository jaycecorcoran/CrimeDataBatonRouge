cmake_minimum_required(VERSION 3.26)
project(Prog3)

set(CMAKE_CXX_STANDARD 17)


set(SFML_STATIC_LIBRARIES TRUE)
set(DCSV2_BUILD_TESTS TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories("C:/SFML/include/SFML" "C:/csv2/include/csv2")

add_executable(Prog3 main.cpp
        Window.cpp
        Window.h
        ZipWindow.h
        ZipWindow.cpp
        CityWindow.cpp
        CityWindow.h
        CSVParser.h
        CSVParser.cpp
        csv2/include/csv2/mio.hpp
        csv2/include/csv2/parameters.hpp
        csv2/single_include/csv2/csv2.hpp
)

target_link_libraries(Prog3 sfml-system sfml-window sfml-graphics sfml-audio)

