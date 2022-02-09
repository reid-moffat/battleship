/**
 * A coordinate objects stores an x and y position in the range [0, 9]
 * Used to refer to squares on the battleship board
 */

#ifndef BATTLESHIP_COORDINATE_H
#define BATTLESHIP_COORDINATE_H

#include <iostream>

using std::ostream;

namespace entity {

    class Coordinate {
    public:
        /**
         * Initialize this coordinate with a position of (0, 0)
         */
        Coordinate();

        /**
         * Initialize this coordinate with a specified x and y value
         */
        Coordinate(int x, int y);

        /**
         * Returns the x position of this coordinate
         */
        [[nodiscard]] int getX() const;

        /**
         * Returns the y position of this coordinate
         */
        [[nodiscard]] int getY() const;

        /**
         * Returns true if both coordinates have the same x and y values
         */
        bool operator==(const Coordinate &rhs) const;

        /**
         * Returns true if this coordinate's x OR y is less than the other coordinates'
         * x or y respectively
         */
        bool operator<(const Coordinate &rhs) const;

        /**
         * Outputs this coordinate in the form (x, y)
         */
        friend ostream &operator<<(std::ostream &output, const Coordinate &coord);

    private:
        // Coordinate x position
        int x;

        // Coordinate y position
        int y;
    };

    class CoordinateException : std::exception {
    public:
        explicit CoordinateException(const char *message);
        [[nodiscard]] const char *what() const noexcept override;

    private:
        const char *errorMessage;
    };
}// namespace entity

#endif//BATTLESHIP_COORDINATE_H
