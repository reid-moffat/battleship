include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(secondTest test1.cpp)

target_link_libraries(secondTest gtest gtest_main)
#target_link_libraries(firstTest ../include ../src)
