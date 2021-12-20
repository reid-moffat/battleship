/**
 * Free helper functions for various functions such as SFML objects, error handling
 * and numerical calculations
 */

#ifndef BATTLESHIP_HELPERS_H
#define BATTLESHIP_HELPERS_H

#include "enums/shipNames.hpp"
#include <SFML/Graphics.hpp>
#include <random>

using entity::shipNames;
using std::string;

/**
 * Returns the size of a ship from its enum value
 */
constexpr int shipSize(shipNames name) noexcept {
    return (int) static_cast<std::underlying_type_t<shipNames>>(name) + 1;
}

/**
 * Returns a random integer in the range [start, end] (both inclusive)
 */
inline int randomInt(int start, int end) {
    static std::random_device rd; // Obtain a random number from hardware
    static std::mt19937 eng(rd());// Seed the generator
    std::uniform_int_distribution<> dist(start, end);
    return dist(eng);
}

/**
 * Loads a texture from the given path
 *
 * Note: The texture path has to be relative to res/images
 * For example, "homepage/ActivePlayButton.png"
 */
inline void loadTexture(sf::Texture &texture, const string &path) {
    if (!texture.loadFromFile("../res/images/" + path)) {
        exit(-1);
    }
}

/**
 * Initializes a sprite with a texture, position and scale
 */
inline void setSprite(sf::Vector2f position, sf::Vector2f scale, const sf::Texture &spriteTexture, sf::Sprite &sprite) {
    sprite.setTexture(spriteTexture);
    sprite.setPosition(position);
    sprite.setScale(scale);
}

/**
 * Updates a Vector2f object with the current mouse position
 */
inline void updateMousePosition(sf::RenderWindow &gui, sf::Vector2f &mousePosition) {
    mousePosition = gui.mapPixelToCoords(sf::Mouse::getPosition(gui));
}

#endif//BATTLESHIP_HELPERS_H
