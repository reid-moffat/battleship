/**
 * Grid class header
 * Provides a player's grid
 *
 */

#ifndef BATTLESHIP_GRID_H
#define BATTLESHIP_GRID_H

#include "coordinate.hpp"
#include "shipNames.hpp"
#include "squareType.hpp"
#include <memory>
#include <vector>

using std::map;
using std::tuple;
using std::unique_ptr;
using std::vector;

namespace entity {

    class Grid {
    public:
        /**
         * Constructs a grid
         * Constructs a grid with a list of ships
         *
         * @param ships the six ships on the grid with their orientations
         * @param isEnvironment if this is not for a real player, but for the environment
         * @param ships the six ships on the grid with their orientations in the form
         *              nameOfShip: (topLeftCoordinate, isHorizontal)
         */
        explicit Grid(const map<shipsNames, tuple<Coordinate, bool>> &shipOrientations);

        /**
         * Tries to attack a grid square
         *
         * This will return the current status of the grid square (before attacking) and
         * provide the required functionality:
         * 1. If the square is water, change it to hit water
         * 2. If the square is a ship, change it to a hit ship and update the ship that was hit
         * 3. If the square is a hit ship (or hit water), do nothing (attack doesn't go through)
         */
        SquareType attack(Coordinate coord);

        /**
         * Returns the status (whether it has been sunk) of each ship on the board
         */
        map<shipsNames, bool> getShipStatus();

        /**
         * Returns the location of each ship on this board
         * (top-left square and if it is horizontal)
         */
        map<shipsNames, tuple<Coordinate, bool>> getShips();

        /**
         * Default, empty constructor (allows static grids to be initialized without data)
         */
        Grid();

        // Big three
        Grid(Grid &other);
        ~Grid();
        Grid &operator=(Grid *other);

    private:
        /**
         * The six ships on this board
         * Includes their name, the coordinates of squares they occupy and the number of hits on this ship
         */
        map<shipsNames, tuple<Coordinate *, int>> ships;

        /**
         * The location of each ship on this board
         * (top-left square and if it is horizontal)
         */
        map<shipsNames, tuple<Coordinate, bool>> shipPositions;

        /**
         * 10-by-10 array of grid squares
         */
        SquareType **squares;

        /**
         * Size of the grid (both width and height) i.e 10
         */
        static constexpr int size = 10;

    };
}// namespace entity

#endif//BATTLESHIP_GRID_H
