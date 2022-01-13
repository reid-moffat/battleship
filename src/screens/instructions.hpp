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
         *
         */
        static Instructions &getInstance();

        /**
         * Copy constructor
         */
        Instructions(const Instructions &source) = delete;

        /**
         * Overloaded assignment operator
         */
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
        enum textureNames { Background_,
                            IdleBackButton,
                            ActiveBackButton };
        enum spriteNames { Background };
        enum buttonNames { BackButton } ;

    };
}// namespace screen

#endif// BATTLESHIP_INSTRUCTIONS_H