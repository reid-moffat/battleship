/**
 *
 */

#ifndef BATTLESHIP_RESOURCEMANAGER_H
#define BATTLESHIP_RESOURCEMANAGER_H

#include "helperFunctions.hpp"

using std::map;

class ImagesManager {
public:
    /**
     *
     */
    ImagesManager();

    /**
     * Returns a reference to the specified texture
     */
    sf::Texture &getTexture(const unsigned int name);

    /**
     * Returns a reference to the specified sprite
     */
    sf::Sprite &getSprite(const unsigned int name);

private:
    /**
     *
     */
    map<int, sf::Texture> textures;

    /**
     *
     */
    map<int, sf::Sprite> sprites;
};


#endif//BATTLESHIP_RESOURCEMANAGER_H
