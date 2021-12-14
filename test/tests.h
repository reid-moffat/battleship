/**
 * Provides helpful code for test files
 */

#ifndef TEST_TESTS_H
#define TEST_TESTS_H

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

// Helpful assertion formats for debugging (prints all useful error info)
#define ASSERT(statement)                                                                                                      \
    {                                                                                                                          \
        if (!statement) {                                                                                                      \
            std::string path = __FILE__;                                                                                       \
            std::stringstream errMsg;                                                                                          \
            errMsg << "\n\nASSERT FAILED: " << #statement << std::endl                                                         \
                   << "Value: " << statement << std::endl                                                                      \
                   << "Location: " << path.substr(path.find("battleship\\test")) << " (line " << __LINE__ << ")" << std::endl; \
            throw std::invalid_argument(errMsg.str());                                                                         \
        }                                                                                                                      \
    }

#define ASSERT_OPERATION(left, operator, right)                                                       \
    {                                                                                                 \
        if (!((left) operator(right))) {                                                              \
            std::string path = __FILE__;                                                              \
            std::stringstream errMsg;                                                                 \
            errMsg << "\n\nASSERT FAILED: " << #left << " " << #operator<< " " << #right << std::endl \
                   << "Value: " << left << " " << #operator<< " " << right << std::endl               \
                   << "Location: " << path.substr(path.find("battleship\\test"))                      \
                   << " (line " << __LINE__ << ")" << std::endl;                                      \
            throw std::invalid_argument(errMsg.str());                                                \
        }                                                                                             \
    }

#endif//TEST_TESTS_H
