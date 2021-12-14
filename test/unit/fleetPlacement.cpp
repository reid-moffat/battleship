/**
* Test cases for the fleet placement screen
*/

#include "../../include/screen/fleetPlacement.h"

using screen::FleetPlacement;

int main() {
    // Test 1: Ensure the screen can be instantiated
    FleetPlacement fpTest;

    // Test 2: Test the screen
    sf::RenderWindow rw;
    fpTest.run(rw);

    return 0;
}
