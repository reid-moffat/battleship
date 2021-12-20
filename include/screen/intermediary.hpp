/**
 * File: intermediary.h
 * Description: Front-end class that defines the behaviour of the Intermediary screen
 */

#ifndef BATTLESHIP_INTERMEDIARY_H
#define BATTLESHIP_INTERMEDIARY_H

#include "../entity/button.hpp"
#include "screenTemplate.hpp"

#include <SFML/System.hpp>

using entity::Button;

namespace screen {
    class Intermediary : public ScreenTemplate {
    private:
        /**
         * P1 background texture
         */
        sf::Texture intermediaryP1BackgroundTexture;

        /**
         * P2 background texture
         */
        sf::Texture intermediaryP2BackgroundTexture;

        /**
         * Idle continue button texture
         */
        sf::Texture idleContinueButtonTexture;

        /**
         * Active continue button texture
         */
        sf::Texture activeContinueButtonTexture;

        /**
         * Background P1 sprite
         */
        sf::Sprite backgroundP1Sprite;

        /**
         * Background P2 sprite
         */
        sf::Sprite backgroundP2Sprite;

        /**
         * Continue button 
         */
        Button *continueButton;

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
         *
         */
        static Intermediary *instance;

        /**
         * Constructor
         */
        Intermediary();

    public:
        /**
         *
         */
        static Intermediary &getInstance();

        /**
         * Copy constructor
         */
        Intermediary(const Intermediary &source) = delete;

        /**
         * Overloaded assignment operator
         */
        Intermediary &operator=(const Intermediary &source) = delete;

        /**
         * Overridden run method of screenTemplate
         */
        void run() override;
    };
}// namespace screen

#endif// BATTLESHIP_INTERMEDIARY_H