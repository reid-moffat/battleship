/**
 *  Header file for the Coordinate class.
 */

#ifndef BATTLESHIP_COORDINATE_H
#define BATTLESHIP_COORDINATE_H

#include <exception>
#include <iostream>

namespace entity {
    class Coordinate {
    private:
        /**
         * Coordinate x position
         */
        int x;

        /**
         * Coordinate y position
         */
        int y;

    public:
        /**
         * Returns the x position of this coordinate
         */
        [[nodiscard]] int getX() const;

        /**
         * Returns the y position of this coordinate
         */
        [[nodiscard]] int getY() const;

        // Constructors
        Coordinate();
        Coordinate(int xVal, int yVal);

        // Overloaded operators
        bool operator==(const Coordinate &rhs) const;

    };

    // Non-member operator overloading
    bool operator<(const Coordinate &left, const Coordinate &right);
    std::ostream &operator<<(std::ostream &output, const Coordinate &coord);

    class CoordinateException : std::exception {
    public:
        explicit CoordinateException(const char *message);
        [[nodiscard]] const char *what() const noexcept override;

    private:
        const char *errorMessage;
    };
};    // namespace entity
#endif//BATTLESHIP_COORDINATE_H
