/**
 *
 */

#include <sstream>
#include "ImagesManager.hpp"

ImagesManager::ImagesManager(const std::string texturePaths[], const std::string spritePaths[]) {
    int currIndex = 0;
    for (auto x : *texturePaths) {
        this->textures.emplace_back();
        if (!this->textures[currIndex].loadFromFile("../res/images/" + texturePaths[currIndex])) {
            exit(-1);
        }
        currIndex++;
    }

    currIndex = 0;
    for (auto x : *spritePaths) {
        this->sprites.emplace_back();
//        sprites[currIndex].setTexture(spriteTexture); // TODO
//        sprites[currIndex].setPosition(position);
//        sprites[currIndex].setScale(scale);
        currIndex++;
    }
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
