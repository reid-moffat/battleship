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
         * Returns the instance of this screen
         */
        static Intermediary &getInstance();

        // Do not allow copying of this screen's instance
        Intermediary(const Intermediary &source) = delete;

        // Do not allow assignment of this screen's instance
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
            IntermediaryP1BackgroundTexture,
            IntermediaryP2BackgroundTexture,

            IdleContinueButtonTexture,
            ActiveContinueButtonTexture
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