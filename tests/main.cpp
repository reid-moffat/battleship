/**
 * Connects and runs all of the tests with GoogleTest
 */

#include <experimental/filesystem>
#include <gtest/gtest.h>

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    const int testResult = RUN_ALL_TESTS();

    std::experimental::filesystem::remove_all("../test");
    return testResult;
}
