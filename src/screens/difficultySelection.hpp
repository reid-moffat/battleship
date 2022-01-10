/**
 * File: difficultySelection.h
 * Description: Front-end class that defines the behaviour of the Difficulty selection screens
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
        /**
         * Singleton instance
         */
        static std::unique_ptr<DifficultySelection> instance;

        /**
         * Singleton constructor
         */
        DifficultySelection();

        // SFML event loop helpers
        void update() override;
        void poll() override;
        void render() override;

        /**
         * Names to refer to the textures on this screen
         */
        enum textureNames { Background,
                            IdlePlayButton,
                            ActivePlayButton };

        /**
         * Names to refer to the sprites on this screen
         */
        enum spriteNames { Backgrounds };

        /**
         * Play button
         */
        std::unique_ptr<Button> playButton;

        /**
         * Background texture
         */
        sf::Texture difficultyBackgroundTexture;

        /**
         * Idle easy button texture
         */
        sf::Texture idleEasyButtonTexture;

        /**
         * Active easy button texture
         */
        sf::Texture activeEasyButtonTexture;

        /**
         * Idle hard button texture
         */
        sf::Texture idleHardButtonTexture;

        /**
         * Active hard button texture
         */
        sf::Texture activeHardButtonTexture;

        /**
         * Idle back button texture
         */
        sf::Texture idleBackButtonTexture;

        /**
         * Active back button texture
         */
        sf::Texture activeBackButtonTexture;

        /**
         * Idle instructions button texture
         */
        sf::Texture idleInstructionsButton;

        /**
         * Active instructions button texture
         */
        sf::Texture activeInstructionsButton;

        /**
         * Background sprite
         */
        sf::Sprite backgroundSprite;

        /**
         * Easy button
         */
        std::unique_ptr<Button> easyButton;

        /**
         * Hard button
         */
        std::unique_ptr<Button> hardButton;

        /**
         * Back button
         */
        std::unique_ptr<Button> backButton;

        /**
         * Instructions button
         */
        std::unique_ptr<Button> instructionsButton;
    };
}// namespace screen

#endif// BATTLESHIP_DIFFICULTYSELECTION_H