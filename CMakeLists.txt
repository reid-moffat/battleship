#
# Application configuration (for test, load test/CMakeLists.txt)
#
cmake_minimum_required(VERSION 3.20)
project(battleship C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

file(GLOB SOURCE_FILES CONFIGURE_DEPENDS
        "src/*.hpp"
        "src/**/*.hpp"
        "src/*.cpp"
        "src/**/*.cpp")

add_executable(battleship ${SOURCE_FILES})

# Add SFML
set(SFML_DIR include/SFML/lib/cmake/SFML)
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML COMPONENTS graphics system REQUIRED)
target_link_libraries(battleship sfml-graphics sfml-system)

add_subdirectory(test)
