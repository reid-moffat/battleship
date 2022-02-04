/**
 * Description: Front-end class that defines the behaviour of the Game Over screens
 */

#ifndef BATTLESHIP_GAMEOVER_H
#define BATTLESHIP_GAMEOVER_H

#include "../controllers/screenTemplate.hpp"
#include "../entity/button.hpp"
#include <SFML/System.hpp>

using entity::Button;

namespace screen {
    class GameOver : public ScreenTemplate {
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

    private:
        // Singleton instance
        static std::unique_ptr<GameOver> instance;

        // Singleton constructor
        GameOver();

        // SFML event loop helpers
        void update() override;
        void poll() override;
        void render() override;

        // Names to refer to resources on this screen
        enum textureNames {
            GameOverWinBackground,
            GameOverLoseBackground,
            GameOverP1Background,
            GameOverP2Background,
            IdleHomepageButton,
            ActiveHomepageButton
        };
        enum spriteNames {
            BackgroundWin,
            BackgroundLose,
            BackgroundP1,
            BackgroundP2
        };
        enum buttonNames {
            Homepage
        };
    };
}// namespace screen

#endif// BATTLESHIP_GAMEOVER_H
