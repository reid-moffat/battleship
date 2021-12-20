#
# Application configuration (for test, load test/CMakeLists.txt)
#
cmake_minimum_required(VERSION 3.20)
project(battleship C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(SFML_DIR include/SFML/lib/cmake/SFML)
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

file(GLOB SOURCE_FILES CONFIGURE_DEPENDS
        "include/*.hpp"
        "include/**/*.hpp"
        "src/*.hpp"
        "src/**/*.hpp"
        "src/*.cpp"
        "src/**/*.cpp")

add_executable(battleship ${SOURCE_FILES})
target_link_libraries(battleship sfml-graphics sfml-audio)
#add_subdirectory(test)
