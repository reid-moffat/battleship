/**
 * Test cases for the environment
 *
 * These tests ensure that the program's environment does not regress, attempting to catch
 * any deleted required files or fatal changes in structure
 */

#include "../tests.h"
#include <gtest/gtest.h>
#include <sys/stat.h>

using std::string;

/**
 * Returns true if a file exists
 */
inline bool fileExists(const string &name) {
    struct stat buffer {};
    return stat(name.c_str(), &buffer) == 0;
}

TEST(Environment, envtest) {
    ASSERT("Making sure there are no environment issues...");

    // Ensures essential files are present
    string files[] = {
            "build", "include", "res", "src", "tests", ".gitignore", "README.md",// Require repo structure/files
            "build/cmake_modules/FindSFML.cmake", "build/assets",    // Application build files
            "CMakeLists.txt"                               // Test build files
    };

    for (const string &file : files) {
        try {
            ASSERT(fileExists("../../" + file))
        } catch (std::invalid_argument &e) {
            throw std::invalid_argument("A required file is missing: " + file);
        }
    }
}
