/**
 * Enumeration for the states that a square on the board can be in
 */

#ifndef BATTLESHIP_SQUARETYPE_H
#define BATTLESHIP_SQUARETYPE_H

namespace entity {

    enum SquareType {
        WATER,
        HIT_WATER,
        SHIP,
        HIT_SHIP,
    };

}

#endif//BATTLESHIP_SQUARETYPE_H
