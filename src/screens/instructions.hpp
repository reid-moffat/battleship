/**
 * File: instructions.h
 * Description: Front-end class that defines the behaviour of the Instructions screens
 */

#ifndef BATTLESHIP_INSTRUCTIONS_H
#define BATTLESHIP_INSTRUCTIONS_H

#include "../entity/button.hpp"
#include "../controllers/screenTemplate.hpp"

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
         * System event
         */
        sf::Event event{};

        /**
         * Calls helpers::updateMousePosition() and entity::Button::updateButtonState()
         */
        void update();

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
        Instructions();

        /**
         *
         */
        static Instructions *instance;

    public:
        /**
         *
         */
        static Instructions &getInstance();

        /**
         * Copy constructor
         */
        Instructions(const Instructions &source) = delete;

        /**
         * Overloaded assignment operator
         */
        Instructions &operator=(const Instructions &source) = delete;

        /**
         * Overridden run method of screenTemplate
         */
        void run() override;
    };
}// namespace screens

#endif// BATTLESHIP_INSTRUCTIONS_H