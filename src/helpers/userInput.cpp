/**
 * Helper functions for SFML user input implementation
 */

#include "../../include/helpers/userInput.h"

void updateMousePosition(sf::RenderWindow &gui, sf::Vector2f &mousePosition) {
    mousePosition = gui.mapPixelToCoords(sf::Mouse::getPosition(gui));
}
