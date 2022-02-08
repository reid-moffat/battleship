/**
 * File: instructions.h
 * Description: Front-end class that defines the behaviour of the Instructions screens
 */

#ifndef BATTLESHIP_INSTRUCTIONS_H
#define BATTLESHIP_INSTRUCTIONS_H

#include "../controllers/screenTemplate.hpp"
#include "../entity/button.hpp"
#include <SFML/System.hpp>

using entity::Button;

namespace screen {
    class Instructions : public ScreenTemplate {
    public:
        /**
         * Returns the instance of this screen
         */
        static Instructions &getInstance();

// Do not allow copying of this screen's instance
        Instructions(const Instructions &source) = delete;

        // Do not allow assignment of this screen's instance
        Instructions &operator=(const Instructions &source) = delete;

    private:
        // Singleton instance
        static std::unique_ptr<Instructions> instance;

        // Singleton constructor
        Instructions();

        // SFML event loop helpers
        void update() override;
        void poll() override;
        void render() override;

        // Names to refer to resources on this screen
        enum textureNames {
            BackgroundTexture,

            IdleBackButtonTexture,
            ActiveBackButtonTexture
        };
        enum spriteNames {
            Background
        };
        enum buttonNames {
            BackButton
        };
    };
}// namespace screen

#endif// BATTLESHIP_INSTRUCTIONS_H