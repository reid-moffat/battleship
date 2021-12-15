/**
 * Helper functions for SFML user input implementation
 */

#include "../../include/helpers/userInput.hpp"

void updateMousePosition(sf::RenderWindow &gui, sf::Vector2f &mousePosition) {
    mousePosition = gui.mapPixelToCoords(sf::Mouse::getPosition(gui));
}
