/**
 * Description: Front-end class that defines the behaviour of the Homepage screens
 */

#ifndef BATTLESHIP_HOMEPAGE_H
#define BATTLESHIP_HOMEPAGE_H

#include "../entity/button.hpp"
#include "../controllers/screenTemplate.hpp"
#include <SFML/System.hpp>

using entity::Button;

namespace screen {
    class Homepage : public ScreenTemplate {
    public:
        /**
         *
         */
        static Homepage &getInstance();

        /**
         * Overridden run method of screenTemplate
         */
        void run() override;

        /**
         * Copy constructor
         */
        Homepage(const Homepage &source) = delete;

        /**
         * Overloaded assignment operator
         */
        Homepage &operator=(const Homepage &source) = delete;

    private:
        /**
         * Singleton instance
         */
        static Homepage *instance;

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
        Homepage();

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
    };
}// namespace screens

#endif// BATTLESHIP_HOMEPAGE_H