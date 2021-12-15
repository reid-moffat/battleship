/**
 * File: difficultySelection.h
 * Description: Front-end class that defines the behaviour of the Difficulty selection screen
 */

#ifndef BATTLESHIP_DIFFICULTYSELECTION_H
#define BATTLESHIP_DIFFICULTYSELECTION_H

#include "../entity/button.h"
#include "screenTemplate.h"
#include <SFML/System.hpp>

using entity::Button;

namespace screen {
    class DifficultySelection : public ScreenTemplate {
    private:
        /**
         * Background texture
         */
        sf::Texture difficultyBackgroundTexture;

        /**
         * Idle easy button texture
         */
        sf::Texture idleEasyButtonTexture;

        /**
         * Active easy button texture
         */
        sf::Texture activeEasyButtonTexture;

        /**
         * Idle hard button texture
         */
        sf::Texture idleHardButtonTexture;

        /**
         * Active hard button texture
         */
        sf::Texture activeHardButtonTexture;

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
        sf::Texture idleInstructionsButton;

        /**
         * Active instructions button texture
         */
        sf::Texture activeInstructionsButton;

        /**
         * Background sprite
         */
        sf::Sprite backgroundSprite;

        /**
         * Easy button
         */
        Button *easyButton;

        /**
         * Hard button
         */
        Button *hardButton;

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

    public:
        /**
         * Constructor
         */
        DifficultySelection();

        /**
         * Copy constructor
         */
        DifficultySelection(const DifficultySelection &source);

        /**
         * Destructor
         */
        ~DifficultySelection() override;

        /**
         * Overloaded assignment operator
         */
        DifficultySelection &operator=(const DifficultySelection &source);

        /**
         * Overridden run method of screenTemplate
         */
        void run(sf::RenderWindow &gui) override;
    };
}// namespace screen

#endif// BATTLESHIP_DIFFICULTYSELECTION_H