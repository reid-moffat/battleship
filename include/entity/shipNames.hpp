/**
 *
 */

#ifndef BATTLESHIP_SHIPNAMES_H
#define BATTLESHIP_SHIPNAMES_H

#include <map>

using std::map;

namespace entity {
    enum shipsNames {
        ROW_BOAT,
        PATROL_BOAT,
        SUBMARINE,
        DESTROYER,
        AIRCRAFT_CARRIER,
        BATTLESHIP
    };

    static map<shipsNames, int> shipSizes = {{ROW_BOAT, 1},
                                             {PATROL_BOAT, 2},
                                             {SUBMARINE, 3},
                                             {DESTROYER, 4},
                                             {AIRCRAFT_CARRIER, 5},
                                             {BATTLESHIP, 6}};

}// namespace entity

#endif//BATTLESHIP_SHIPNAMES_H
