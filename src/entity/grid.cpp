/**
 * Grid class implementation
 *
 */

#include "../../include/entity/grid.hpp"

using entity::Coordinate;
using entity::Grid;
using entity::shipsNames;
using entity::SquareType;
using std::get;


Grid::Grid(const map<shipsNames, tuple<Coordinate, bool>> &shipOrientations) {
    // Initialize the grid itself with all water to start
    squares = new SquareType *[size];
    for (int i = 0; i < size; ++i) {
        squares[i] = new SquareType[size];
        for (int j = 0; j < size; ++j) {
            squares[i][j] = WATER;
        }
    }

    // Create the ship objects
    for (auto const &ship : shipOrientations) {
        int x = get<0>(ship.second).getX();// Topmost/leftmost square x and y
        int y = get<0>(ship.second).getY();
        const bool horizontal = get<1>(ship.second);                         // If the ship is horizontally aligned
        get<0>(ships[ship.first]) = new Coordinate[shipSizes[ship.first]];// Array of coordinates this ship occupies

        for (int i = 0; i < shipSizes[ship.first]; ++i) {
            // Initializes the i^th square (from the top left)
            if (horizontal) {
                get<0>(ships[ship.first])[i] = Coordinate(x + i, y);
                squares[y][x + i] = SHIP;
            } else {
                get<0>(ships[ship.first])[i] = Coordinate(x, y + i);
                squares[y + i][x] = SHIP;
            }
        }
        get<1>(ships[ship.first]) = 0;// Initialize hit count to 0
    }
}

SquareType Grid::attack(Coordinate coord) {
    // Determine the type of the square
    SquareType *status = &squares[coord.getY()][coord.getX()];
    if (*status == WATER) { // We need to note if water has been hit
        *status = HIT_WATER;
        return WATER;
    } else if (*status != SHIP) { // HIT_SHIP or HIT_WATER (do nothing)
        return *status;
    }

    // If it's not water or an already hit square, it is a ship. Find which ship it is and update it
    *status = HIT_SHIP;
    for (auto const &ship : this->ships) {
        // Loop through the squares in this ship
        Coordinate *coords = get<0>(ship.second);
        for (int i = 0; i < shipSizes[ship.first]; ++i) {
            if (coords[i] == coord) {       // Found it!
                get<1>(ships[ship.first])++;// Update hit count
                return SHIP;
            }
        }
    }
    throw std::invalid_argument("Ship was not found- this game is in an impossible state!");
}

map<shipsNames, bool> Grid::getShipStatus() {
    map<shipsNames, bool> shipStatuses;
    for (auto const &ship : this->ships) {
        // If this ship has as many hits as it has squares, it has been sunk
        shipStatuses[ship.first] = get<1>(ship.second) == shipSizes[ship.first];
    }
    return shipStatuses;
}

map<shipsNames, tuple<Coordinate, bool>> entity::Grid::getShips() {
    map<shipsNames, tuple<Coordinate, bool>> shipPositions;
    for (auto const &ship: ships) {
        get<0>(shipPositions[ship.first]) = get<0>(ship.second)[0];
        get<1>(shipPositions[ship.first]) = get<1>(ship.second);
    }
    return shipPositions;
}

entity::Grid::Grid() {
    ;
}


// Big three
Grid::~Grid() {
    for (int i = 0; i < size; ++i) {
        delete[] squares[i];
    }
    delete[] squares;
}

Grid::Grid(Grid &grid) {
    // Copy the other ship's coordinates and number of hits
    for (auto const &ship : grid.ships) {
        *get<0>(ships[ship.first]) = *get<0>(ship.second);
        get<1>(ships[ship.first]) = get<1>(ship.second);
    }

    // Copy the grid
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            this->squares[i][j] = grid.squares[i][j];
        }
    }
}

Grid &Grid::operator=(Grid *rhs) {
    if (this == rhs) return *this;

    this->ships.clear();
    for (const auto ship : rhs->ships) {
        this->ships.insert(ship);
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            squares[i][j] = rhs->squares[i][j];
        }
    }
    return *this;
}
