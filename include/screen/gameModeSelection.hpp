/**
 * File: gameModeSelection.h
 * Description: Front-end class that defines the behaviour of the Game Mode selection screen
 */

#ifndef BATTLESHIP_GAMEMODESELECTION_H
#define BATTLESHIP_GAMEMODESELECTION_H

#include "../entity/button.hpp"
#include "screenTemplate.hpp"

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
         * Mouse position vector
         */
        sf::Vector2f mousePosition;

        /**
         * System event
         */
        sf::Event event{};

        /**
         * Calls helpers::updateMousePosition() and entity::Button::updateButtonState()
         */
        void update(sf::RenderWindow &gui, sf::Vector2f mousePosition);

        /**
         * Polls for system events
         */
        void poll(sf::RenderWindow &gui);

        /**
         * Renders all sprites
         */
        void render(sf::RenderWindow &gui);

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

        /**
         * Overridden run method of screenTemplate
         */
        void run() override;
    };
}// namespace screen

#endif// BATTLESHIP_GAMEMODESELECTION_H