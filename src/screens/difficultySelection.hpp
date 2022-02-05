/**
 * Front-end class that defines the behaviour of the Difficulty selection screens
 */

#ifndef BATTLESHIP_DIFFICULTYSELECTION_H
#define BATTLESHIP_DIFFICULTYSELECTION_H

#include "../controllers/screenTemplate.hpp"
#include "../entity/button.hpp"
#include <SFML/System.hpp>

using entity::Button;

namespace screen {
    class DifficultySelection : public ScreenTemplate {
    public:
        /**
         *
         */
        static DifficultySelection &getInstance();

        /**
         * Copy constructor
         */
        DifficultySelection(const DifficultySelection &source) = delete;

        /**
         * Overloaded assignment operator
         */
        DifficultySelection &operator=(const DifficultySelection &source) = delete;

    private:
        // Singleton instance
        static std::unique_ptr<DifficultySelection> instance;

        // Singleton constructor
        DifficultySelection();

        // SFML event loop helpers
        void update() override;
        void poll() override;
        void render() override;

        // Names to refer to resources on this screen
        enum textureNames {
            Background_,
            IdleEasyButton,
            ActiveEasyButton,
            IdleHardButton,
            ActiveHardButton,
            IdleBackButton,
            ActiveBackButton,
            IdleInstructionsButton,
            ActiveInstructionsButton
        };
        enum spriteNames {
            Background
        };
        enum buttonNames {
            EasyButton,
            HardButton,
            BackButton,
            InstructionsButton
        };
    };
}// namespace screen

#endif// BATTLESHIP_DIFFICULTYSELECTION_H
