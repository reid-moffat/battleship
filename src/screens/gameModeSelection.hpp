/**
 * Front-end class that defines the behaviour of the Game Mode selection screens
 */

#ifndef BATTLESHIP_GAMEMODESELECTION_H
#define BATTLESHIP_GAMEMODESELECTION_H

#include "../controllers/screenTemplate.hpp"

namespace screen {
    class GameModeSelection : public ScreenTemplate {
    public:
        /**
         * Returns the instance of this screen
         */
        static GameModeSelection &getInstance();

        // Do not allow copying of this screen's instance
        GameModeSelection(const GameModeSelection &source) = delete;

        // Do not allow assignment of this screen's instance
        GameModeSelection &operator=(const GameModeSelection &source) = delete;

    private:
        // Singleton instance
        static std::unique_ptr<GameModeSelection> instance;

        // Singleton constructor
        GameModeSelection();

        // SFML event loop helpers
        void update() override;
        void poll() override;
        void render() override;

        // Names to refer to resources on this screen
        enum textureNames {
            Background_,

            IdleOnePlayerButtonTexture,
            ActiveOnePlayerButtonTexture,
            IdleTwoPlayerButtonTexture,
            ActiveTwoPlayerButtonTexture,
            IdleBackButtonTexture,
            ActiveBackButtonTexture,
            IdleInstructionsButtonTexture,
            ActiveInstructionsButtonTexture
        };
        enum spriteNames {
            Background
        };
        enum buttonNames {
            OnePlayer,
            TwoPlayers,
            Back,
            Instructions
        };
    };
}// namespace screen

#endif// BATTLESHIP_GAMEMODESELECTION_H