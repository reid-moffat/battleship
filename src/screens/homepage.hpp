/**
 * Description: Front-end class that defines the behaviour of the Homepage screens
 */

#ifndef BATTLESHIP_HOMEPAGE_H
#define BATTLESHIP_HOMEPAGE_H

#include "../controllers/screenTemplate.hpp"
#include "../entity/button.hpp"

using entity::Button;
using std::map;

namespace screen {
    class Homepage : public ScreenTemplate {
    public:
        /**
         *
         */
        static Homepage &getInstance();

        /**
         * Overridden run method of screenTemplate
         */
        void run() override;

        /**
         * Copy constructor
         */
        Homepage(const Homepage &source) = delete;

        /**
         * Overloaded assignment operator
         */
        Homepage &operator=(const Homepage &source) = delete;

    private:
        /**
         * Singleton instance
         */
        static std::unique_ptr<Homepage> instance;

        /**
         * Singleton constructor
         */
        Homepage();

        // SFML event loop helpers
        void update();
        void poll();
        void render();

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
    };
}// namespace screen

#endif// BATTLESHIP_HOMEPAGE_H