include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

enable_testing()
add_executable(secondTest test1.cpp)

target_link_libraries(secondTest gtest gtest_main)
#target_link_libraries(secondTest ../../include ../../src)
