#
# Config
#
cmake_minimum_required(VERSION 3.20)
project(battleship-unit-tests)

set(CMAKE_CXX_STANDARD 14)

enable_testing()

file(GLOB SOURCE_FILES
        "../../include/*.h"
        "../../include/**/*.h"
        "../../src/state.cpp"
        "../../src/**/*.cpp"
        )

# Unit tests
#add_executable(sm screenManager.cpp ${SOURCE_FILES})
#add_test(ScreenManager sm)
#
#add_executable(st screenTemplate.cpp ${SOURCE_FILES})
#add_test(ScreenTemplate st)


#
# SFML (don't touch please, except for adding target_link_libraries)
#
include_directories(src include C:/SFML/include)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
#    target_link_libraries(sm ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
#    target_link_libraries(st ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif ()

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

# Copy dlls to build
if (WIN32)
    file(GLOB BINARY_DEP_DLLS "${SFML_INCLUDE_DIR}/../bin/*.dll")
    file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
    file(GLOB MINGW_DEP_DLLS "C:/mingw64/bin/*.dll")
    file(COPY ${MINGW_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif ()
