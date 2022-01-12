/**
 *
 */

#ifndef BATTLESHIP_RESOURCEMANAGER_H
#define BATTLESHIP_RESOURCEMANAGER_H

#include "../entity/button.hpp"
#include "helperFunctions.hpp"

using entity::Button;
using std::tuple;
using std::vector;

class ScreenResourceManager {
public:
    /**
     * Initializes this manager with textures and sprites
     *
     * @param texturePaths paths to textures to load relative to res/images
     * @param sprites data to initialize each sprite:
     *                -The initial position (sf::Vector2f)
     *                -The scale of the sprite (sf::Vector2f)
     *                -The corresponding texture (its index in the texturePaths)
     * @param buttons data to initialize each button:
     *                -The initial position (sf::Vector2f)
     *                -The scale of the button (sf::Vector2f)
     *                -The corresponding texture for when the button is idle (its index in the texturePaths)
     *                -The corresponding texture for when the button is active (its index in the texturePaths)
     */
    ScreenResourceManager(const vector<string> &texturePaths,
                          const vector<tuple<sf::Vector2f, sf::Vector2f, int>> &sprites,
                          const vector<tuple<sf::Vector2f, sf::Vector2f, int, int>> &buttons);

    /**
     * Default constructor
     */
    ScreenResourceManager();

    /**
     * Returns a reference to the texture at the specified index
     */
    sf::Texture &getTexture(int index);

    /**
     * Returns a reference to the sprite at the specified index
     */
    sf::Sprite &getSprite(int index);

    /**
     * Returns a reference to the button at the specified index
     */
    Button &getButton(int index);

private:
    /**
     * All the SFML textures in this manager
     */
    vector<sf::Texture> textures;

    /**
     * All the SFML sprites in this manager
     */
    vector<sf::Sprite> sprites;

    /**
     * All the SFML buttons in this manager
     */
    vector<Button> buttons;
};

#endif//BATTLESHIP_RESOURCEMANAGER_H
