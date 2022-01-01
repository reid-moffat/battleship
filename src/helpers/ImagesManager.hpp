/**
 *
 */

#ifndef BATTLESHIP_RESOURCEMANAGER_H
#define BATTLESHIP_RESOURCEMANAGER_H

#include "helperFunctions.hpp"

using std::vector;
using std::tuple;

class ImagesManager {
public:
    /**
     * Initializes this manager with textures and sprites
     *
     * @param texturePaths paths to textures to load relative to res/images
     * @param sprites data to initialize each sprite:
     *                -The initial position (sf::Vector2f)
     *                -The scale of the sprite (sf::Vector2f)
     *                -The corresponding texture (its index in the texturePaths)
     */
    ImagesManager(const vector<string>& texturePaths, const vector<tuple<sf::Vector2f, sf::Vector2f, int>>& sprites);

    /**
     * Default constructor
     */
    ImagesManager();

    /**
     * Returns a reference to the texture at the specified index
     */
    sf::Texture &getTexture(int index);

    /**
     * Returns a reference to the sprite at the specified index
     */
    sf::Sprite &getSprite(int index);

private:
    /**
     * All the SFML textures in this manager
     */
    vector<sf::Texture> textures;

    /**
     * All the SFML sprites in this manager
     */
    vector<sf::Sprite> sprites;
};

#endif//BATTLESHIP_RESOURCEMANAGER_H
