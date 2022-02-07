/**
 * Front-end class that defines the behaviour of the Intermediary screens
 */

#ifndef BATTLESHIP_INTERMEDIARY_H
#define BATTLESHIP_INTERMEDIARY_H

#include "../controllers/screenTemplate.hpp"
#include "../entity/button.hpp"
#include <SFML/System.hpp>

using entity::Button;

namespace screen {
    class Intermediary : public ScreenTemplate {
    public:
        /**
         *
         */
        static Intermediary &getInstance();

        /**
         * Copy constructor
         */
        Intermediary(const Intermediary &source) = delete;

        /**
         * Overloaded assignment operator
         */
        Intermediary &operator=(const Intermediary &source) = delete;

    private:
        // Singleton instance
        static std::unique_ptr<Intermediary> instance;

        // Singleton constructor
        Intermediary();

        // SFML event loop helpers
        void update() override;
        void poll() override;
        void render() override;

        // Names to refer to resources on this screen
        enum textureNames {
            IntermediaryP1Background,
            IntermediaryP2Background,
            IdleContinueButton,
            ActiveContinueButton
        };
        enum spriteNames {
            BackgroundP1,
            BackgroundP2
        };
        enum buttonNames {
            ContinueButton
        };
    };
}// namespace screen

#endif// BATTLESHIP_INTERMEDIARY_H