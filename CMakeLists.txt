#
# Application and tests configuration
#
cmake_minimum_required(VERSION 3.20)
project(battleship C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Application build
file(GLOB SOURCE_FILES CONFIGURE_DEPENDS
        "src/**/*.hpp"
        "src/**/*.cpp")

add_executable(battleship src/main.cpp ${SOURCE_FILES})


# Test build (using googletest)
enable_testing()
add_subdirectory(include/googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

file(GLOB TEST_FILES CONFIGURE_DEPENDS
        "test/architecture/*.cpp"
        "test/unit/*.cpp"
        "test/integration/*.cpp"
        "test/system/*.cpp"
        "test/assertions.hpp")

add_executable(battleship-tests test/main.cpp ${SOURCE_FILES} ${TEST_FILES})


# Add SFML to the builds
set(SFML_DIR include/SFML/lib/cmake/SFML)
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.5 COMPONENTS graphics system REQUIRED)
target_link_libraries(battleship sfml-graphics sfml-system)
target_link_libraries(battleship-tests PUBLIC gtest gtest_main sfml-graphics sfml-system)
