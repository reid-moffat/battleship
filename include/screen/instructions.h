/**
 * File: instructions.h
 * Description: Front-end class that defines the behaviour of the Instructions screen
 */

#ifndef BATTLESHIP_INSTRUCTIONS_H
#define BATTLESHIP_INSTRUCTIONS_H

#include "../entity/button.h"
#include "screenTemplate.h"

#include <SFML/System.hpp>

using entity::Button;

namespace screen {
    class Instructions : public ScreenTemplate {
    private:
        /**
         * Background texture
         */
        sf::Texture instructionsBackgroundTexture;

        /**
         * Idle back button texture
         */
        sf::Texture idleBackButtonTexture;

        /**
         * Active back button texture
         */
        sf::Texture activeBackButtonTexture;

        /**
         * Background sprite
         */
        sf::Sprite backgroundSprite;

        /**
         * Back button 
         */
        Button *backButton;

        /**
         * Mouse position vector
         */
        sf::Vector2f mousePosition;

        /**
         * System event
         */
        sf::Event event{};

        /**
         * Calls State::updateMousePosition() and entity::Button::updateButtonState()
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
        Instructions();

        /**
         * Copy constructor
         */
        Instructions(const Instructions &source);

        /**
         * Destructor
         */
        ~Instructions();

        /**
         * Overloaded assignment operator
         */
        Instructions &operator=(const Instructions &source);

        /**
         * Overridden run method of screenTemplate
         */
        void run(sf::RenderWindow &gui) override;
    };
}// namespace screen

#endif// BATTLESHIP_INSTRUCTIONS_H