/**
 * Description: Front-end class that defines the behaviour of the Game Over screens
 */

#ifndef BATTLESHIP_GAMEOVER_H
#define BATTLESHIP_GAMEOVER_H

#include "../entity/button.hpp"
#include "../controllers/screenTemplate.hpp"
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
         * Calls helpers::updateMousePosition() and entity::Button::updateButtonState()
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
        GameOver();

        /**
         *
         */
        static GameOver *instance;

    public:
        /**
         *
         */
        static GameOver &getInstance();

        /**
         * Copy constructor
         */
        GameOver(const GameOver &source) = delete;

        /**
         * Overloaded assignment operator
         */
        GameOver &operator=(const GameOver &source) = delete;

        /**
         * Overridden run method of screenTemplate
         */
        void run() override;
    };
}// namespace screens

#endif// BATTLESHIP_GAMEOVER_H