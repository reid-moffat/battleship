/**
 * Free helper functions for various functions such as SFML objects, error handling
 * and numerical calculations
 */

#ifndef BATTLESHIP_HELPERS_H
#define BATTLESHIP_HELPERS_H

#include "../controllers/state.hpp"
#include "../enums/shipNames.hpp"
#include <random>

using entity::shipNames;
using std::string;

/**
 * Returns the size of a ship from its enum value
 */
constexpr int shipSize(const shipNames name) noexcept {
    return (int) static_cast<std::underlying_type_t<shipNames>>(name) + 1;
}

/**
 * Returns a random integer in the range [start, end] (both inclusive)
 */
inline int randomInt(const int start, const int end) {
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
        std::cout << "Error: unable to open file: /res/images/" << path << std::endl;
        exit(-1);
    }
}

/**
 * Initializes a sprite with a texture, position and scale
 */
inline void setSprite(const sf::Vector2f position, const sf::Vector2f scale, const sf::Texture &spriteTexture, sf::Sprite &sprite) {
    sprite.setTexture(spriteTexture);
    sprite.setPosition(position);
    sprite.setScale(scale);
}

#endif//BATTLESHIP_HELPERS_H
