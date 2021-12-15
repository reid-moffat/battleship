/**
 * Helpful assertion macros to print out debugging info for failed test cases
 */

#ifndef BATTLESHIP_ASSERTIONS_H
#define BATTLESHIP_ASSERTIONS_H

#define ASSERT(statement)                                                         \
    {                                                                             \
        if (!statement) {                                                         \
            std::string path = __FILE__;                                          \
            std::stringstream errMsg;                                             \
            errMsg << "\n\nASSERT FAILED: " << #statement << std::endl            \
                   << "Value: " << statement << std::endl                         \
                   << "Location: " << path.substr(path.find("battleship\\tests")) \
                   << " (line " << __LINE__ << ")" << std::endl;                  \
            throw std::invalid_argument(errMsg.str());                            \
        }                                                                         \
    }

#define ASSERT_OPERATION(left, operator, right)                                                       \
    {                                                                                                 \
        if (!((left) operator(right))) {                                                              \
            std::string path = __FILE__;                                                              \
            std::stringstream errMsg;                                                                 \
            errMsg << "\n\nASSERT FAILED: " << #left << " " << #operator<< " " << #right << std::endl \
                   << "Value: " << left << " " << #operator<< " " << right << std::endl               \
                   << "Location: " << path.substr(path.find("battleship/tests"))                      \
                   << " (line " << __LINE__ << ")" << std::endl;                                      \
            throw std::invalid_argument(errMsg.str());                                                \
        }                                                                                             \
    }

#endif//BATTLESHIP_ASSERTIONS_H
