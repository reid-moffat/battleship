/**
 * Description: Front-end class that defines the behaviour of the Game Over screens
 */

#ifndef BATTLESHIP_GAMEOVER_H
#define BATTLESHIP_GAMEOVER_H

#include "../controllers/screenTemplate.hpp"

namespace screen {
    class GameOver : public ScreenTemplate {
    public:
        /**
         * Returns the instance of this screen
         */
        static GameOver &getInstance();

        // Do not allow copying of this screen's instance
        GameOver(const GameOver &source) = delete;

        // Do not allow assignment of this screen's instance
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
            WinBackgroundTexture,
            LoseBackgroundTexture,
            P1BackgroundTexture,
            P2BackgroundTexture,

            IdleHomepageButtonTexture,
            ActiveHomepageButtonTexture
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
