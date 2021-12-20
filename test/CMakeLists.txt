#
# Testing configuration (for the application, load ../CMakeLists.txt))
#
cmake_minimum_required(VERSION 3.20)
project(battleship-tests C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()
add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

file(GLOB SOURCE_FILES CONFIGURE_DEPENDS
        "../src/helpers.hpp"
        "../src/**/*.hpp"
        "../src/**/*.cpp")

file(GLOB TEST_FILES CONFIGURE_DEPENDS
        "architecture/*.cpp"
        "unit/*.cpp"
        "integration/*.cpp"
        "system/*.cpp")

add_executable(battleship-tests main.cpp assertions.hpp ${SOURCE_FILES} ${TEST_FILES})

set(SFML_DIR include/SFML/lib/cmake/SFML)
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.5 COMPONENTS graphics system REQUIRED)
target_link_libraries(battleship-tests PUBLIC gtest gtest_main sfml-graphics sfml-system)
