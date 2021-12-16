/**
 * Helper functions for SFML textures implementation
 */

#include "../../include/helpers/helpers.hpp"

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
