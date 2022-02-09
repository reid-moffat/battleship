/**
 * Enumeration for the states that a square on the board can be in
 */

#ifndef BATTLESHIP_SQUARETYPE_H
#define BATTLESHIP_SQUARETYPE_H

namespace entity {

    enum SquareType {
        Water,
        HitWater,
        Ship,
        HitShip,
    };

}

#endif//BATTLESHIP_SQUARETYPE_H
