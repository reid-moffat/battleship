#
# Config
#
cmake_minimum_required(VERSION 3.20)
project(battleship-tests)

set(CMAKE_CXX_STANDARD 14)


#
# Add your test cases here
#
# PLEASE READ: HOW TO TEST (IMPORTANT):
#  1. Below, add these two lines (replacing the text in <>):
#       add_executable(<executable_name> <path_to_test_file> ${SOURCE_FILES})
#       add_test(<test_name> <executable_name_from_the_last_line>)
#  2. At the end of the "if (SFML_FOUND)" part below (line ~50), add the following:
#       target_link_libraries(<executable_name> ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
#
enable_testing()

file(GLOB SOURCE_FILES
        "../include/*.h"
        "../include/**/*.h"
        "../src/state.cpp"
        "../src/**/*.cpp"
        )

# Environment testing
add_executable(env environment.cpp ${SOURCE_FILES})
add_test(Environment env)

# Unit testing
add_executable(sm unit/screenManager.cpp ${SOURCE_FILES})
add_test(ScreenManager sm)

add_executable(st unit/screenTemplate.cpp ${SOURCE_FILES})
add_test(ScreenTemplate st)


#
# SFML (don't touch please, except for adding target_link_libraries)
#
include_directories(src include C:/SFML/include)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(env ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
    target_link_libraries(sm ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
    target_link_libraries(st ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif ()

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

# Copy dlls to build
if (WIN32)
    file(GLOB BINARY_DEP_DLLS "${SFML_INCLUDE_DIR}/../bin/*.dll")
    file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
    file(GLOB MINGW_DEP_DLLS "C:/mingw64/bin/*.dll")
    file(COPY ${MINGW_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif ()
