/**
 * Free helper functions implementation
 */

#include "../../include/helpers/helpers.hpp"
#include <random>

int randomInt(int start, int end) {
    static std::random_device rd; // Obtain a random number from hardware
    static std::mt19937 eng(rd()); // Seed the generator
    std::uniform_int_distribution<> dist(start, end);
    return dist(eng);
}

void loadTexture(sf::Texture &texture, const std::string &path) {
    if (!texture.loadFromFile("../res/images/" + path)) {
        exit(-1);
    }
}

void setSprite(sf::Vector2f position, sf::Vector2f scale, const sf::Texture &spriteTexture, sf::Sprite &sprite) {
    sprite.setTexture(spriteTexture);
    sprite.setPosition(position);
    sprite.setScale(scale);
}

void updateMousePosition(sf::RenderWindow &gui, sf::Vector2f &mousePosition) {
    mousePosition = gui.mapPixelToCoords(sf::Mouse::getPosition(gui));
}
