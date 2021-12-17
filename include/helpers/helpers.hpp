/**
 * Free helper functions for various functions such as SFML objects, error handling
 * and numerical calculations
 */

#ifndef BATTLESHIP_HELPERS_H
#define BATTLESHIP_HELPERS_H

#include <SFML/Graphics.hpp>
#include "../entity/shipNames.hpp"

using std::string;
using entity::shipNames;

/**
 * Returns the size of a ship from its enum value
 */
constexpr int shipSize(shipNames name) noexcept {
    return (int) static_cast<std::underlying_type_t<shipNames>>(name) + 1;
}

/**
 * Returns a random integer in the range [start, end] (both inclusive)
 */
int randomInt(int start, int end);

/**
 * Loads a texture from the given path
 *
 * Note: The texture path has to be relative to res/images
 * For example, "homepage/ActivePlayButton.png"
 */
void loadTexture(sf::Texture &texture, const string &path);

/**
 * Initializes a sprite with a texture, position and scale
 */
void setSprite(sf::Vector2f position, sf::Vector2f scale, const sf::Texture &spriteTexture, sf::Sprite &sprite);

/**
 * Updates a Vector2f object with the current mouse position
 */
void updateMousePosition(sf::RenderWindow &gui, sf::Vector2f &mousePosition);

#endif//BATTLESHIP_HELPERS_H
