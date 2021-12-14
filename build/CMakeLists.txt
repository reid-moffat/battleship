cmake_minimum_required(VERSION 3.20)
project(battleship)

set(CMAKE_CXX_STANDARD 14)

file(GLOB SOURCE_FILES
        "../include/state.h"
        "../include/entity/*.h"
        "../include/screen/*.h"
        "../include/user/*.h"
        "../src/main.cpp"
        "../src/state.cpp"
        "../src/entity/*.cpp"
        "../src/screen/*.cpp"
        "../src/user/*.cpp"
        )

add_executable(battleship ${SOURCE_FILES})

include_directories(src include C:/SFML/include)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(battleship ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif ()

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

# Copy dlls to build
if (WIN32)
    file(GLOB BINARY_DEP_DLLS "${SFML_INCLUDE_DIR}/../bin/*.dll")
    file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
    file(GLOB MINGW_DEP_DLLS "C:/mingw64/bin/*.dll")
    file(COPY ${MINGW_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif ()
