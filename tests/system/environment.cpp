/**
 * These tests ensure that the program's architecture does not regress, attempting to catch
 * any deleted required files or fatal changes in structure
 */

#include <gtest/gtest.h>
#include <sys/stat.h>

using std::string;

TEST(Environment, envtest) {
    // Ensures required files are present
    const string files[] = {
            // Directory structure
            "build", "googletest", "include", "res", "src", "tests",

            // Build files
            "CMakeLists.txt", "build/assets", "build/assets/.keep", "build/cmake_modules", "build/cmake_modules/FindSFML.cmake",

            // Test files
            "tests/CMakeLists.txt", "tests/main.cpp", "tests/assertions.h", "tests/unit", "tests/integration", "tests/system",

            // VCS files
            ".git", ".gitignore", "README.md", "LICENSE"};

    for (const string &file : files) {
        if (access(("../../" + file).c_str(), F_OK) == -1) {
            throw std::invalid_argument("File/directory not found in repository root: " + file);
        }
    }
}
