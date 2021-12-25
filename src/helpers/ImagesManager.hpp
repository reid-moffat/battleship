/**
 *
 */

#ifndef BATTLESHIP_RESOURCEMANAGER_H
#define BATTLESHIP_RESOURCEMANAGER_H

#include "helperFunctions.hpp"

using std::vector;

class ImagesManager {
public:
    /**
     * Initializes this manager with
     */
    ImagesManager(const std::string texturePaths[], const std::string spritePaths[]);

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
