#
# Config
#
cmake_minimum_required(VERSION 3.20)
project(battleship-tests)
set(CMAKE_CXX_STANDARD 14)


add_subdirectory(lib/googletest)
include_directories(lib/googletest/googletest/include)
include_directories(lib/googletest/googlemock/include)
include_directories(../include)
include_directories(../src)

add_subdirectory(integration)
add_subdirectory(system)
add_subdirectory(unit)


add_executable(battleship-tests main.cpp)
target_link_libraries(battleship-tests gtest gtest_main)




#add_definitions(-std=c++11)
#
#add_executable(all_tests environment.cpp ${SOURCE_FILES})
#
#include_directories(../../include ../../src)
#
#add_subdirectory(unit)
##add_subdirectory(integration) # TODO: configure system and integration subdirectories
##add_subdirectory(system)
#
#target_link_libraries(all_tests ../../include ../../src)
#
#
##if ($ENV{CLION_IDE})
##    message("Call cmake command from the CLion IDE")
##    set(CALENDAR_PATH_VAR "test")
##    set(CALENDAR_DIR_VAR "test")
##endif ()



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
#enable_testing()

# Environment testing
#add_executable(env environment.cpp ${SOURCE_FILES})
#add_test(Environment env)


#
# SFML (don't touch please, except for adding target_link_libraries)
#
include_directories(src include C:/SFML/include)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(battleship-tests ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif ()

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

# Copy dlls to build
if (WIN32)
    file(GLOB BINARY_DEP_DLLS "${SFML_INCLUDE_DIR}/../bin/*.dll")
    file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
    file(GLOB MINGW_DEP_DLLS "C:/mingw64/bin/*.dll")
    file(COPY ${MINGW_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif ()
