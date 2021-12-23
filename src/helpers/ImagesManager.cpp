/**
 *
 */

#include <sstream>
#include "ImagesManager.hpp"

sf::Texture &ImagesManager::getTexture(const int index) {
    if (index > textures.size()) {
        std::ostringstream errMsg;
        errMsg << "Error: must provide an index between 0 and " << textures.size();
        throw std::invalid_argument(errMsg.str());
    }
    return textures[index];
}

sf::Sprite &ImagesManager::getSprite(const int index) {
    if (index > sprites.size()) {
        std::ostringstream errMsg;
        errMsg << "Error: must provide an index between 0 and " << sprites.size();
        throw std::invalid_argument(errMsg.str());
    }
    return sprites[index];
}
