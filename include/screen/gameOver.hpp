/**
 * File: gameOver.h
 * Description: Front-end class that defines the behaviour of the Game Over screen
 */

#ifndef BATTLESHIP_GAMEOVER_H
#define BATTLESHIP_GAMEOVER_H

#include "../entity/button.hpp"
#include "screenTemplate.hpp"

#include <SFML/System.hpp>

using entity::Button;

namespace screen {
    class GameOver : public ScreenTemplate {
    private:
        /**
         * Win background texture
         */
        sf::Texture gameOverWinBackgroundTexture;

        /**
         * Lose background texture
         */
        sf::Texture gameOverLoseBackgroundTexture;

        /**
         * P1 background texture
         */
        sf::Texture gameOverP1BackgroundTexture;

        /**
         * P2 background texture
         */
        sf::Texture gameOverP2BackgroundTexture;

        /**
         * Idle homepage button texture
         */
        sf::Texture idleHomepageButtonTexture;

        /**
         * Active continue button texture
         */
        sf::Texture activeHomepageButtonTexture;

        /**
         * Backgroud win sprite
         */
        sf::Sprite backgroundWinSprite;

        /**
         * Backgroud lose sprite
         */
        sf::Sprite backgroundLoseSprite;

        /**
         * Backgroud P1 sprite
         */
        sf::Sprite backgroundP1Sprite;

        /**
         * Backgroud P2 sprite
         */
        sf::Sprite backgroundP2Sprite;

        /**
         * Homepage button 
         */
        Button *homepageButton;

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
        GameOver();

        /**
         * Copy constructor
         */
        GameOver(const GameOver &source);

        /**
         * Destructor
         */
        ~GameOver();

        /**
         * Overloaded assignment operator
         */
        GameOver &operator=(const GameOver &source);

        /**
         * Overridden run method of screenTemplate
         */
        void run(sf::RenderWindow &gui) override;
    };
}// namespace screen

#endif// BATTLESHIP_GAMEOVER_H