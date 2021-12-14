/**
 * Test cases for the environment
 *
 * These tests ensure that the program's environment does not regress, attempting to catch
 * any deleted required files or fatal changes in structure
 */

#include "../tests.h"
#include <sys/stat.h>

using std::string;

/**
 * Returns true if a file exists
 */
inline bool fileExists(const string &name) {
    struct stat buffer {};
    return stat(name.c_str(), &buffer) == 0;
}

int main() {
    ASSERT("Making sure there are no environment issues...");

    // Ensures essential files are present
    string files[] = {
            "../build", "../include", "../res", "../src", "../test", "../.gitignore", "../README.md",// Require repo structure/files
            "../build/CMakeLists.txt", "../build/cmake_modules/FindSFML.cmake", "../build/assets",   // Application build files
            "CMakeLists.txt", "cmake_modules/FindSFML.cmake", "assets"                               // Test build files
    };
    for (const string &file : files) {
        try {
            // Executable is in cmake-build-debug so ../ needs to be added to each
            ASSERT(fileExists("../" + file));
        } catch (std::invalid_argument &e) {
            throw std::invalid_argument("A required file is missing: " + file);
        }
    }

    return 0;
}
