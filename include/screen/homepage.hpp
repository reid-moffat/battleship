/**
 * File: homepage.h
 * Description: Front-end class that defines the behaviour of the Homepage screen
 */

#ifndef BATTLESHIP_HOMEPAGE_H
#define BATTLESHIP_HOMEPAGE_H

#include "../entity/button.hpp"
#include "screenTemplate.hpp"

#include <SFML/System.hpp>

using entity::Button;

namespace screen {
    class Homepage : public ScreenTemplate {
    private:
        /**
         * Background texture
         */
        sf::Texture homepageBackgroundTexture;

        /**
         * Idle play button texture
         */
        sf::Texture idlePlayButtonTexture;

        /**
         * Active play button texture
         */
        sf::Texture activePlayButtonTexture;

        /**
         * Background sprite
         */
        sf::Sprite backgroundSprite;

        /**
         * Play button 
         */
        Button *playButton;

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
        Homepage();

        /**
         * Copy constructor
         */
        Homepage(const Homepage &source);

        /**
         * Destructor
         */
        ~Homepage();

        /**
         * Overloaded assignment operator
         */
        Homepage &operator=(const Homepage &source);

        /**
         * Overridden run method of screenTemplate
         */
        void run(sf::RenderWindow &gui) override;
    };
}// namespace screen

#endif// BATTLESHIP_HOMEPAGE_H