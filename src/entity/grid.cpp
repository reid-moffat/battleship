/**
 * Grid class implementation
 */

#include "grid.hpp"
#include "../helpers/helperFunctions.hpp"

using entity::Coordinate;
using entity::Grid;
using entity::shipNames;
using entity::SquareType;
using std::get;

Grid::Grid(const map<shipNames, tuple<Coordinate, bool>> &shipPositions) {
    // Initialize the grid itself with all water to start
    for (int i = 0; i < size; ++i) {
        squares.emplace_back(vector<SquareType>());
        for (int j = 0; j < size; ++j) {
            squares[i].push_back(WATER);
        }
    }

    // Create the ship objects
    for (auto const &ship : shipPositions) {
        // Information about the ship
        shipNames shipName = ship.first;
        int x = get<0>(ship.second).getX();         // Topmost/leftmost x coordinate
        int y = get<0>(ship.second).getY();         // Topmost/leftmost y coordinate
        const bool horizontal = get<1>(ship.second);// If the ship is aligned horizontally

        // Array of coordinates this ship occupies
        Coordinate *&coordinates = get<0>(ships[shipName]);
        coordinates = new Coordinate[shipSize(shipName)];

        // Initializes the squares the ship occupies (from the top/left)
        for (int i = 0; i < shipSize(shipName); ++i) {
            coordinates[i] = Coordinate(x, y);
            squares[y][x] = SHIP;
            horizontal ? x++ : y++;
        }

        get<1>(ships[shipName]) = 0;   // Initialize hit count to 0
        shipStatuses[shipName] = false;// Initialize the ship as 'not sunk'
    }

    this->shipPositions = shipPositions;
}

SquareType Grid::attack(Coordinate &coord) {
    // Determine the type of the square
    SquareType &status = squares[coord.getY()][coord.getX()];
    if (status == WATER) {// We need to note if water has been hit
        status = HIT_WATER;
        return WATER;
    } else if (status != SHIP) {// HIT_SHIP or HIT_WATER (do nothing)
        return status;
    }

    // If it's not water or an already hit square, it is a ship. Find which ship it is and update it
    status = HIT_SHIP;
    for (auto const &ship : this->ships) {
        shipNames shipName = ship.first;
        int &hitCount = get<1>(ships[shipName]);

        // Loop through the squares in this ship to see if it was hit
        Coordinate *coords = get<0>(ship.second);
        for (int i = 0; i < shipSize(shipName); ++i) {
            if (coords[i] == coord) {// Found it!
                hitCount++;
                if (hitCount == shipSize(shipName)) {
                    shipStatuses[shipName] = true;// Ship has been sunk
                }
                return SHIP;
            }
        }
    }
    throw std::invalid_argument("Ship was not found- this game is in an impossible state!");
}

map<shipNames, tuple<Coordinate, bool>> &entity::Grid::getShips() {
    return this->shipPositions;
}

map<shipNames, bool> &Grid::getShipStatus() {
    return this->shipStatuses;
}

entity::Grid::Grid() {
    ;
}
