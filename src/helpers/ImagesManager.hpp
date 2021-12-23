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
    ImagesManager();

    /**
     * Returns a reference to the specified texture
     */
    sf::Texture &getTexture(int index);

    /**
     * Returns a reference to the specified sprite
     */
    sf::Sprite &getSprite(int index);

private:
    /**
     *
     */
    vector<sf::Texture> textures;

    /**
     *
     */
    vector<sf::Sprite> sprites;
};


#endif//BATTLESHIP_RESOURCEMANAGER_H
