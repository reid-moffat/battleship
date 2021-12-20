/**
 * These test ensure that the program's architecture does not regress, attempting to catch
 * any deleted or renamed required files
 */

#include <gtest/gtest.h>
#include <sys/stat.h>

using std::string;

TEST(Architecture, requiredFiles) {
    // Ensures required files are present
    const string files[] = {
            // Directory structure
            "bin", "include", "res", "src", "test",

            // Build files
            "CMakeLists.txt", "include/SFML",

            // Test files
            "test/CMakeLists.txt", "test/googletest", "test/include/SFML", "test/main.cpp",
            "test/assertions.hpp", "test/unit", "test/integration", "test/system",
            "test/architecture",

            // VCS files
            ".git", ".gitignore", "README.md", "LICENSE"};


    // Note: The current working directory of the test is the build/ folder; the same as the actual
    // application. This means we don't have to change the relative paths when referring to files
    for (const string &file : files) {
        if (access(("../" + file).c_str(), F_OK) == -1) {
            throw std::invalid_argument("File/directory not found in repository root: " + file);
        }
    }
}