/**
 * Front-end class that defines the behaviour of the Game Mode selection screens
 */

#ifndef BATTLESHIP_GAMEMODESELECTION_H
#define BATTLESHIP_GAMEMODESELECTION_H

#include "../controllers/screenTemplate.hpp"
#include "../entity/button.hpp"
#include <SFML/System.hpp>

using entity::Button;

namespace screen {
    class GameModeSelection : public ScreenTemplate {
    public:
        /**
         *
         */
        static GameModeSelection &getInstance();

        /**
         * Copy constructor
         */
        GameModeSelection(const GameModeSelection &source) = delete;

        /**
         * Overloaded assignment operator
         */
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
            IdleOnePlayer,
            ActiveOnePlayer,
            IdleTwoPlayer,
            ActiveTwoPlayer,
            IdleBackButton,
            ActiveBackButton,
            IdleInstructionsButton,
            ActiveInstructionsButton
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