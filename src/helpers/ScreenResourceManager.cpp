/**
 *
 */

#include "ScreenResourceManager.hpp"
#include <sstream>

using std::get;

ScreenResourceManager::ScreenResourceManager(const vector<string>& texturePaths, const vector<tuple<sf::Vector2f, sf::Vector2f, int>>& spritesData) {
    for (int i = 0; i < texturePaths.size(); ++i) {
        // Add a new texture
        this->textures.emplace_back();

        // Attempt to load the texture image
        auto texture = &this->textures[i];
        if (!texture->loadFromFile("../res/images/" + texturePaths[i])) {
            exit(-1);
        }
    }

    for (int i = 0; i < spritesData.size(); ++i) {
        // Add a new sprite
        this->sprites.emplace_back();

        // Set the required data for the sprite
        auto sprite = &this->sprites[i];
        sprite->setPosition(get<0>(spritesData[i]));
        sprite->setScale(get<1>(spritesData[i]));
        sprite->setTexture(textures[get<2>(spritesData[i])]);
    }
}

sf::Texture &ScreenResourceManager::getTexture(const int index) {
    if (index > textures.size()) {
        std::ostringstream errMsg;
        errMsg << "Error: must provide an index between 0 and " << textures.size() << "; " << index << " is invalid";
        throw std::invalid_argument(errMsg.str());
    }
    return textures[index];
}

sf::Sprite &ScreenResourceManager::getSprite(const int index) {
    if (index > sprites.size()) {
        std::ostringstream errMsg;
        errMsg << "Error: must provide an index between 0 and " << sprites.size() << "; " << index << " is invalid";
        throw std::invalid_argument(errMsg.str());
    }
    return sprites[index];
}

Button &ScreenResourceManager::getButton(const int index) {
    if (index > sprites.size()) {
        std::ostringstream errMsg;
        errMsg << "Error: must provide an index between 0 and " << buttons.size() << "; " << index << " is invalid";
        throw std::invalid_argument(errMsg.str());
    }
    return buttons[index];
}

ScreenResourceManager::ScreenResourceManager() = default;
