/**
 *
 */

#ifndef BATTLESHIP_RESOURCEMANAGER_H
#define BATTLESHIP_RESOURCEMANAGER_H

#include "../entity/button.hpp"
#include "helperFunctions.hpp"

// Required data to initialize a sprite: std::tuple<sf::Vector2f, sf::Vector2f, int>
typedef std::tuple<sf::Vector2f, sf::Vector2f, int> sprite;
// Required data to initialize a button: std::tuple<sf::Vector2f, sf::Vector2f, int, int>
typedef std::tuple<sf::Vector2f, sf::Vector2f, int, int> button;

using entity::Button;
using std::tuple;
using std::vector;

class ScreenResourceManager {
public:
    /**
     * Initializes this manager with textures and sprites
     *
     * @param screenName the name of the screen i.e folder in res/images/ where the textures are located
     *                   (do not include a leading or trailing forward slash)
     * @param texturePaths paths to textures to load relative to res/images/[<i>screenName</i>]
     * @param sprites data to initialize each sprite:<p>
     *                -The initial position (sf::Vector2f)<p>
     *                -The scale of the sprite (sf::Vector2f)<p>
     *                -The corresponding texture (its index in the texturePaths)
     * @param buttons data to initialize each button:<p>
     *                -The initial position (sf::Vector2f)<p>
     *                -The scale of the button (sf::Vector2f)<p>
     *                -The corresponding texture for when the button is idle (its index in the texturePaths)<p>
     *                -The corresponding texture for when the button is active (its index in the texturePaths)
     */
    ScreenResourceManager(const string& screenName,
                          const vector<string> &texturePaths,
                          const vector<sprite> &sprites,
                          const vector<button> &buttons);

    /**
     * Default constructor
     */
    ScreenResourceManager();

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
