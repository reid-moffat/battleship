/**
 * Helper functions to provide encapsulation for sprite-related methods
 * such as loading a texture from a path and setting a sprite object
 */

#ifndef BATTLESHIP_SPRITES_H
#define BATTLESHIP_SPRITES_H

#include <SFML/Graphics.hpp>

using std::string;

/**
 * Loads a texture from the given path
 *
 * Note: The texture path has to be relative to res/images
 * For example, "homepage/ActivePlayButton.png"
 */
void loadTexture(sf::Texture &texture, const string &path);

/**
 * Initializes a sprite
 */
void setSprite(sf::Vector2f position, sf::Vector2f scale, const sf::Texture &spriteTexture, sf::Sprite &sprite);

#endif//BATTLESHIP_SPRITES_H
