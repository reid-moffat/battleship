/**
 *
 */

#include <sstream>
#include "ImagesManager.hpp"

ImagesManager::ImagesManager(const std::string texturePaths[], const std::string spritePaths[]) {
    for (auto x : *texturePaths) {
        this->textures.emplace_back();
        this->textures[0]; // TODO: Load from file
    }
    // TODO: Do the same for the sprites
}

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
