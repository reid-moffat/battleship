/**
 * The global game state. This static class stores data about the current
 * state of the game for screens to use and update
 *
 * Because the state does not require most classes, it will not cause a circular
 * dependency like screenManager would if screens included it in their headers
 */

#ifndef BATTLESHIP_STATE_H
#define BATTLESHIP_STATE_H

#include "screen/screens.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using screen::Screens;
using std::string;

class State {
private:
    /**
     * The screen that is currently being rendered
     */
    static Screens current;

    /**
     * The previously rendered screen
     *
     * Used by the information screen since multiple possible screens could
     * switch to it, and thus we do not know what screen to return to. Also
     * makes going back easier and less buggy
     */
    static Screens previous;

public:
    /**
     * Screen lock condition (if this is true, no user input can be registered)
     */
    static bool lockedFlag;

    /**
     * The possible game modes: SinglePlayer and MultiPlayer
     */
    enum GameMode { SinglePlayer,
                    MultiPlayer };

    /**
     * The selected game mode (SinglePlayer or MultiPlayer)
     */
    static GameMode gameMode;

    /**
     * The possible game difficulties: Easy and Hard
     */
    enum Difficulty { EASY,
                      HARD };

    /**
     * The selected difficulty
     */
    static Difficulty difficulty;

    /**
     * The two player 'names': P1 and P2
     */
    enum Player { P1,
                  P2 };

    /**
     * The current player (who is selecting their fleet/attacking currently)
     */
    static Player player;

    /**
     * Width of the window in pixels
     */
    inline static const int width = 1920;

    /**
     * Height of the window in pixels
     */
    inline static const int height = 1080;

    /**
     * Returns the current screen
     */
    static Screens getCurrentScreen();

    /**
     * Returns the previous screen
     */
    static Screens getPreviousScreen();

    /**
     * Changes the currently rendered screen to the specified screen
     */
    static void changeScreen(Screens newScreen);

    /**
     * Changes to the previous screen (used for back buttons)
     */
    static void previousScreen();

    /**
     * Loads a texture from the given path
     *
     * Note: The texture path is relative to res/images
     * For example, "homepage/ActivePlayButton.png"
     */
    static void loadTexture(sf::Texture &texture, const string &path);

    /**
     * Initializes a sprite
     */
    static void setSprite(sf::Vector2f position, sf::Vector2f scale, const sf::Texture &spriteTexture, sf::Sprite &sprite);

    /**
     * Updates the current mouse position of a Vector2f object
     */
    static void updateMousePosition(sf::RenderWindow &gui, sf::Vector2f &mousePosition);
};

#endif// BATTLESHIP_STATE_H
