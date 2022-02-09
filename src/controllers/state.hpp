/**
 * The global game state. This static class stores data about the current
 * state of the game for screens to use and update
 *
 * Because the state does not require most classes, it will not cause a circular
 * dependency like screenManager would if screens included it in their headers
 */

#ifndef BATTLESHIP_STATE_H
#define BATTLESHIP_STATE_H

#include "../enums/screens.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

using screen::Screens;
using std::string;
using std::unique_ptr;

class State {
public:
    /**
     * Game window- all sprites should be rendered here
     */
    static unique_ptr<sf::RenderWindow> gui;

    /**
     * Stores the current SFML event (MouseClicked, Closed, etc)
     */
    static sf::Event event;

    /**
     * Screen lock condition (if this is true, no user input will be registered)
     */
    static bool lockedFlag;

    /**
     * The possible game modes: SINGLE_PLAYER and MULTI_PLAYER
     */
    enum GameMode { SINGLE_PLAYER,
                    MULTI_PLAYER };

    /**
     * The selected game mode (SINGLE_PLAYER or MULTI_PLAYER)
     */
    static GameMode gameMode;

    /**
     * The possible game difficulties: EASY and HARD
     */
    enum Difficulty { EASY,
                      HARD };

    /**
     * The selected difficulty (EASY or HARD)
     */
    static Difficulty difficulty;

    /**
     * The two player 'names': P1 and P2
     */
    enum Player { P1,
                  P2 };

    /**
     * The current player (who is selecting their fleet/attacking currently): P1 or P2
     */
    static Player player;

    /**
     * Width of the window in pixels
     */
    constexpr static int width = 1920;

    /**
     * Height of the window in pixels
     */
    constexpr static int height = 1080;

    /**
     * Returns the current screens (enum name)
     */
    static Screens getCurrentScreen();

    /**
     * Returns the previous screens (enum name)
     */
    static Screens getPreviousScreen();

    /**
     * Changes the currently rendered screens to the specified screens
     */
    static void changeScreen(Screens newScreen);

    /**
     * Changes to the previous screens (used for back buttons)
     */
    static void previousScreen();

    /**
     * Returns the current mouse position as a 2-d vector of floats
     */
    static sf::Vector2f getMousePosition();

private:
    // The screen that is currently being rendered
    static Screens current;

    // The previously rendered screen
    static Screens previous;
};

#endif// BATTLESHIP_STATE_H
