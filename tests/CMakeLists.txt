#
# Config
#
cmake_minimum_required(VERSION 3.20)
project(battleship-tests)
set(CMAKE_CXX_STANDARD 14)

file(GLOB TEST_FILES CONFIGURE_DEPENDS
        "integration/*.cpp"
        "system/*.cpp"
        "unit/*.cpp")

add_executable(battleship-tests main.cpp assertions.h ${TEST_FILES})
target_link_libraries(battleship-tests gtest gtest_main)


#
# SFML
#
include_directories(src include C:/SFML/include)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../build/cmake_modules")
find_package(SFML REQUIRED system window graphics)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(battleship-tests ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif ()

file(COPY ../build/assets DESTINATION ${CMAKE_BINARY_DIR})

# Copy dlls to build
if (WIN32)
    file(GLOB BINARY_DEP_DLLS "${SFML_INCLUDE_DIR}/../bin/*.dll")
    file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
    file(GLOB MINGW_DEP_DLLS "C:/mingw64/bin/*.dll")
    file(COPY ${MINGW_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif ()
