include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(firstTest test.cpp)

target_link_libraries(firstTest gtest gtest_main)
#target_link_libraries(firstTest ../include ../src)
