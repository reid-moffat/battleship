/**
 * File: gameModeSelection.h
 * Description: Front-end class that defines the behaviour of the Game Mode selection screens
 */

#ifndef BATTLESHIP_GAMEMODESELECTION_H
#define BATTLESHIP_GAMEMODESELECTION_H

#include "../controllers/screenTemplate.hpp"
#include "../entity/button.hpp"
#include <SFML/System.hpp>

using entity::Button;

namespace screen {
    class GameModeSelection : public ScreenTemplate {
    private:
        /**
         * Background texture
         */
        sf::Texture gameModeBackgroundTexture;

        /**
         * Idle 1 player button texture
         */
        sf::Texture idleOnePlayerButtonTexture;

        /**
         * Active 1 player button texture
         */
        sf::Texture activeOnePlayerButtonTexture;

        /**
         * Idle 2 player button texture
         */
        sf::Texture idleTwoPlayerButtonTexture;

        /**
         * Active 2 player button texture
         */
        sf::Texture activeTwoPlayerButtonTexture;

        /**
         * Idle back button texture
         */
        sf::Texture idleBackButtonTexture;

        /**
         * Active back button texture
         */
        sf::Texture activeBackButtonTexture;

        /**
         * Idle instructions button texture
         */
        sf::Texture idleInstructionsButtonTexture;

        /**
         * Active instructions button texture
         */
        sf::Texture activeInstructionsButtonTexture;

        /**
         * Background sprite
         */
        sf::Sprite backgroundSprite;

        /**
         * 1 Player button
         */
        Button *onePlayerButton;

        /**
         * 2 Player button
         */
        Button *twoPlayerButton;

        /**
         * Back button
         */
        Button *backButton;

        /**
         * Instructions button
         */
        Button *instructionsButton;

        /**
         * Updates the buttons on this screen
         */
        void update();

        /**
         * Polls for system events
         */
        void poll();

        /**
         * Renders all sprites
         */
        void render();

        /**
         * Constructor
         */
        GameModeSelection();

        /**
         *
         */
        static GameModeSelection *instance;

    public:
        /**
         *
         */
        static GameModeSelection &getInstance();

        /**
         * Copy constructor
         */
        GameModeSelection(const GameModeSelection &source) = delete;

        /**
         * Overloaded assignment operator
         */
        GameModeSelection &operator=(const GameModeSelection &source) = delete;

    };
}// namespace screen

#endif// BATTLESHIP_GAMEMODESELECTION_H