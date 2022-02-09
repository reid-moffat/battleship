/**
 * Stores a player's grid i.e the status of each square
 */

#ifndef BATTLESHIP_GRID_H
#define BATTLESHIP_GRID_H

#include "../enums/shipNames.hpp"
#include "../enums/squareType.hpp"
#include "coordinate.hpp"
#include <map>
#include <vector>

using std::map;
using std::tuple;
using std::vector;

namespace entity {

    class Grid {
    public:
        /**
         * Constructs a grid with a list of ships
         *
         * @param ships the six ships on the grid with their orientations
         * @param isEnvironment if this is not for a real player, but for the environment
         * @param ships the six ships on the grid with their orientations in the form
         *              nameOfShip: (topLeftCoordinate, isHorizontal)
         */
        explicit Grid(const map<shipNames, tuple<Coordinate, bool>> &shipOrientations);

        /**
         * Tries to attack a grid square
         *
         * This will return the current status of the grid square (before attacking) and
         * provide the required functionality:
         * 1. If the square is water, change it to hit water
         * 2. If the square is a ship, change it to a hit ship and update the ship that was hit
         * 3. If the square is a hit ship (or hit water), do nothing (attack doesn't go through)
         */
        SquareType attack(Coordinate &coord);

        /**
         * Returns the location of each ship on this board
         * (top-left square and if it is horizontal)
         */
        map<shipNames, tuple<Coordinate, bool>> &getShips();

        /**
         * Returns the status (whether it has been sunk) of each ship on the board
         */
        map<shipNames, bool> &getShipStatus();

        /**
         * Default, empty constructor
         */
        Grid();

        /**
         * Size of the grid (both width and height)
         */
        static constexpr int size = 10;

    private:
        /**
         * The six ships on this board
         * This map maps the six ships (their enumerated name) to:
         *  -The coordinates it occupies on the board
         *  -The number of hits on this ship
         */
        map<shipNames, tuple<vector<Coordinate>, int>> ships;

        /**
         * Each ship with its top/left coordinate and whether it is horizontal or not
         * Used to render the ships to the screens
         */
        map<shipNames, tuple<Coordinate, bool>> shipPositions;

        /**
         * Whether each ship has been sunk or not
         * USed to determine if the game has been finished and what ships have been sunk
         */
        map<shipNames, bool> shipStatuses;

        /**
         * 10-by-10 array of grid squares
         */
        vector<vector<SquareType>> squares;
    };
}// namespace entity

#endif//BATTLESHIP_GRID_H
