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
#include <string>

using screen::Screens;

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
     * Screen lock condition
     */
    static bool lockedFlag;

    /**
     * Enum of game modes
     */
    enum GameMode { SinglePlayer,
                    MultiPlayer };

    /**
     * Selected game mode
     */
    static GameMode gameMode;

    /**
     * Enum of difficulties
     */
    enum Difficulty { EASY,
                      HARD };

    /**
     * Selected difficulty
     */
    static Difficulty difficulty;

    /**
     * Enum of player types
     */
    enum Player { P1,
                  P2 };

    /**
     * Current player
     */
    static Player player;

    /**
     * Width of the window in pixels
     */
    static const int width;

    /**
     * Height of the window in pixels
     */
    static const int height;

    /**
     * Loads a texture from the given path
     */
    static void loadTexture(sf::Texture &texture, const std::string &path);

    /**
     * Initializes a sprite
     */
    static void setSprite(sf::Vector2f position, sf::Vector2f scale, const sf::Texture &spriteTexture, sf::Sprite &sprite);

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
     * Returns to the previous screen (used for back buttons)
     */
    static void previousScreen();

    /**
     * Updates the current mouse position 
     */
    static void updateMousePosition(sf::RenderWindow &gui, sf::Vector2f &mousePosition);
};

#endif// BATTLESHIP_STATE_H
