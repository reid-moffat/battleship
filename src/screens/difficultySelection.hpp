/**
 * Front-end class that defines the behaviour of the Difficulty selection screens
 */

#ifndef BATTLESHIP_DIFFICULTYSELECTION_H
#define BATTLESHIP_DIFFICULTYSELECTION_H

#include "../controllers/screenTemplate.hpp"

namespace screen {
    class DifficultySelection : public ScreenTemplate {
    public:
        /**
         * Returns the instance of this screen
         */
        static DifficultySelection &getInstance();

        // Do not allow copying of this screen's instance
        DifficultySelection(const DifficultySelection &source) = delete;

        // Do not allow assignment of this screen's instance
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
