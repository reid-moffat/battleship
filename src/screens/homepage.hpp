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
         * Copy constructor
         */
        Homepage(const Homepage &source) = delete;

        /**
         * Overloaded assignment operator
         */
        Homepage &operator=(const Homepage &source) = delete;

    private:
        // Singleton instance
        static std::unique_ptr<Homepage> instance;

        // Singleton constructor
        Homepage();

        // SFML event loop helpers
        void update() override;
        void poll() override;
        void render() override;

        // Names to refer to resources on this screen
        enum textureNames { Background_,
                            IdlePlayButton,
                            ActivePlayButton };
        enum spriteNames { Background };
        enum buttonNames { PlayButton } ;

    };
}// namespace screen

#endif// BATTLESHIP_HOMEPAGE_H