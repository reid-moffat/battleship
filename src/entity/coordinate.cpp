/**
 * Coordinate class implementation
 */

#include "coordinate.hpp"
#include <string>

using entity::Coordinate;

Coordinate::Coordinate() {
    this->x = 0;
    this->y = 0;
}

Coordinate::Coordinate(int xVal, int yVal) {
    try {
        if (xVal > 9 || xVal < 0 || yVal > 9 | yVal < 0) {
            std::string errMsgString = "Error: X and y coordinates must be in the range [0, 9]. x value: " +
                                       std::to_string(xVal) + ", y value: " + std::to_string(yVal);
            throw entity::CoordinateException(errMsgString.c_str());
        } else {
            this->x = xVal;
            this->y = yVal;
        }
    } catch (const CoordinateException &e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
}

int Coordinate::getX() const {
    return x;
}

int Coordinate::getY() const {
    return y;
}

bool Coordinate::operator==(const Coordinate &rhs) const {
    return this->x == rhs.x && this->y == rhs.y;
}
bool entity::Coordinate::operator<(const Coordinate &rhs) const {
    return this->x < rhs.getX() || this->y < rhs.getY();
}

ostream &operator<<(ostream &output, const Coordinate &coord) {
    output << "(" << coord.getX() << ", " << coord.getY() << ")";
    return output;
}


entity::CoordinateException::CoordinateException(const char *message) {
    this->errorMessage = message;
}

const char *entity::CoordinateException::what() const noexcept {
    return errorMessage;
}
