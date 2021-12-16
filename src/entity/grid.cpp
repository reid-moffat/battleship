/**
 * Grid class implementation
 */

#include "../../include/entity/grid.hpp"

using entity::Coordinate;
using entity::Grid;
using entity::shipsNames;
using entity::SquareType;
using std::get;


Grid::Grid(const map<shipsNames, tuple<Coordinate, bool>> &shipOrientations) {
    // Initialize the grid itself
    squares = new SquareType *[size];
    for (int i = 0; i < size; i++) {
        squares[i] = new SquareType[size];
        for (int k = 0; k < size; k++) {
            squares[i][k] = WATER;
        }
    }

    // Create the ship objects
    for (auto const &ship : shipOrientations) {
        int x = get<0>(ship.second).getX();// Topmost/leftmost square x and y
        int y = get<0>(ship.second).getY();
        const bool horizontal = get<1>(ship.second);                         // If the ship is horizontally aligned
        get<0>((*ships)[ship.first]) = new Coordinate[shipSizes[ship.first]];// Array of coordinates this ship occupies

        for (int i = 0; i < shipSizes[ship.first]; ++i) {
            // Initializes the i^th square (from the top left)
            x = horizontal ? x + i : x; // If the ship is horizontal, we move right each time
            y = horizontal ? y : y + i;
            get<0>((*ships)[ship.first])[i] = Coordinate(x, y);
            squares[y][x] = SHIP;
        }
        get<1>((*ships)[ship.first]) = 0;// Initialize hit count to 0

        // Also store the ship's orientation
        (*this->shipPositions)[ship.first] = ship.second;
    }
}

SquareType Grid::attack(Coordinate coord) {
    // Determine the type of the square
    SquareType *status = &squares[coord.getY()][coord.getX()];
    if (*status == WATER) {
        *status = HIT_WATER;
        return WATER;
    } else if (*status != SHIP) {// HIT_SHIP or HIT_WATER (do nothing)
        return *status;
    }

    // Since this is a ship, find the ship in this square and hit it
    *status = HIT_SHIP;
    for (auto const &ship : *this->ships) {
        // Loop through the squares in this ship
        Coordinate *coords = get<0>(ship.second);
        for (int i = 0; i < shipSizes[ship.first]; ++i) {
            if (coords[i] == coord) {          // Found it!
                get<1>((*ships)[ship.first])++;// Update hit count
                return SHIP;
            }
        }
    }
    throw std::invalid_argument("Ship was not found- this game is in an impossible state!");
}

map<shipsNames, bool> Grid::getShipStatus() {
    map<shipsNames, bool> shipStatuses;// Maps a ship to if it has been sunk or not
    for (auto const &ship : *this->ships) {
        // If a ship is sunk, this means all of its squares have been hit
        shipStatuses[ship.first] = get<1>(ship.second) == shipSizes[ship.first];
    }
    return shipStatuses;
}

map<shipsNames, tuple<Coordinate, bool>> entity::Grid::getShips() {
    return *shipPositions;
}

entity::Grid::Grid() = default;


// Big three
Grid::Grid(Grid &grid) {
    for (const auto ship : *grid.ships) {
        this->ships->insert(ship);
    }

    for (const auto ship : *grid.shipPositions) {
        this->shipPositions->insert(ship);
    }

    squares = new SquareType *[size];
    for (int i = 0; i < size; ++i) {
        squares[i] = new SquareType[size];
        for (int j = 0; j < size; ++j) {
            squares[i][j] = grid.squares[i][j];
        }
    }
}

Grid::~Grid() {
    for (int i = 0; i < size; ++i) {
        delete[] squares[i];
    }
    delete[] squares;
}

Grid &Grid::operator=(Grid *rhs) {
    if (this == rhs) return *this;

    this->ships->clear();
    for (const auto ship : *rhs->ships) {
        this->ships->insert(ship);
    }

    this->shipPositions->clear();
    for (const auto ship : *rhs->shipPositions) {
        this->shipPositions->insert(ship);
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            squares[i][j] = rhs->squares[i][j];
        }
    }
    return *this;
}
