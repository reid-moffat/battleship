/**
 * Helper functions to provide common user input functionality, such as
 * getting the current mouse position
 */

#ifndef BATTLESHIP_USERINPUT_H
#define BATTLESHIP_USERINPUT_H

#include <SFML/Graphics.hpp>

/**
 * Updates a Vector2f object with the current mouse position
 */
void updateMousePosition(sf::RenderWindow &gui, sf::Vector2f &mousePosition);

#endif//BATTLESHIP_USERINPUT_H
