/**
 * Coordinate class implementation
 *
 */

#include "../../include/entity/coordinate.h"
#include <string>

using entity::Coordinate;

Coordinate::Coordinate() {
    // No input creates a coordinate at (0,0)
    x = 0;
    y = 0;
}

Coordinate::Coordinate(int xVal, int yVal) {
    try {
        if ((xVal > 9 || xVal < 0) || (yVal > 9 | yVal < 0)) {
            // Since the exception class extends std::exception, it needs to pass
            // a const char* as a parameter i.e a bunch of conversions are required
            std::string errMsgString = "Error: X and y coordinates must be in the range [0, 9]. x value: " + std::to_string(x) + " y value: " + std::to_string(y);
            const char *errMsg = errMsgString.c_str();
            throw entity::CoordinateException(errMsg);
        } else {
            x = xVal;
            y = yVal;
        }
    } catch (const CoordinateException &e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
}

// Getter: x
int Coordinate::getX() const {
    return x;
}

// Getter: y
int Coordinate::getY() const {
    return y;
}

bool Coordinate::operator==(const Coordinate &rhs) const {
    return this->x == rhs.x && this->y == rhs.y;
}

namespace entity {
    bool operator<(const Coordinate &left, const Coordinate &right) {
        return (left.getX() < right.getX() || left.getY() < right.getY());
    }

    std::ostream &operator<<(std::ostream &output, const Coordinate &coord) {
        output << coord.getX() << ", " << coord.getY();
        return output;
    }
}// namespace entity

entity::CoordinateException::CoordinateException(const char *message) {
    this->errorMessage = message;
}

const char *entity::CoordinateException::what() const noexcept {
    return errorMessage;
}