/**
 * Manages SFML textures, sprites and buttons, allowing for automatic loading
 * and less required member variables
 */

#include "ScreenResourceManager.hpp"
#include <sstream>

using std::get;

ScreenResourceManager::ScreenResourceManager(const string& screenName,
                                             const vector<string> &texturePaths,
                                             const vector<tuple<sf::Vector2f, sf::Vector2f, int>> &spritesData,
                                             const vector<tuple<sf::Vector2f, sf::Vector2f, int, int>> &buttons) {
    // Initialize the textures
    for (int i = 0; i < texturePaths.size(); ++i) {
        this->textures.emplace_back(); // Add a new texture

        // Attempt to load the texture image
        sf::Texture &texture = this->textures[i];
        string texturePath = screenName + "/" + texturePaths[i];
        loadTexture(texture, texturePath);
    }

    // Initialize the sprites
    for (int i = 0; i < spritesData.size(); ++i) {
        this->sprites.emplace_back(); // Add a new sprite

        // Get the required data for the sprite
        auto sprite = &this->sprites[i];
        auto const position = get<0>(spritesData[i]);
        auto const scale = get<1>(spritesData[i]);
        auto const *texture = &textures[get<2>(spritesData[i])];

        // Initialize the sprite with its required data
        sprite->setPosition(position);
        sprite->setScale(scale);
        sprite->setTexture(*texture);
    }

    // Initialize the buttons
    for (const auto &button : buttons) {
        // Get the button data
        auto const position = get<0>(button);
        auto const scale = get<1>(button);
        auto *idleTexture = &textures[get<2>(button)];
        auto *activeTexture = &textures[get<3>(button)];

        this->buttons.emplace_back(position, scale, *idleTexture, *activeTexture);
    }
}

sf::Sprite &ScreenResourceManager::getSprite(const int index) {
    if (index > sprites.size()) {
        std::ostringstream errMsg;
        errMsg << "Sprite Error: must provide an index between 0 and " << sprites.size() << "; " << index << " is invalid";
        throw std::invalid_argument(errMsg.str());
    }
    return sprites[index];
}

Button &ScreenResourceManager::getButton(const int index) {
    if (index > buttons.size()) {
        std::ostringstream errMsg;
        errMsg << "Button Error: must provide an index between 0 and " << buttons.size() << "; " << index << " is invalid";
        throw std::invalid_argument(errMsg.str());
    }
    return buttons[index];
}
