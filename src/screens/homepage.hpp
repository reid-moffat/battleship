/**
 * Description: Front-end class that defines the behaviour of the Homepage screens
 */

#ifndef BATTLESHIP_HOMEPAGE_H
#define BATTLESHIP_HOMEPAGE_H

#include "../controllers/screenTemplate.hpp"

namespace screen {
    class Homepage : public ScreenTemplate {
    public:
        /**
         * Returns the instance of this screen
         */
        static Homepage &getInstance();

        // Do not allow copying of this screen's instance
        Homepage(const Homepage &source) = delete;

        // Do not allow assignment of this screen's instance
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
        enum textureNames {
            BackgroundTexture,
            IdlePlayButtonTexture,
            ActivePlayButtonTexture
        };
        enum spriteNames {
            Background
        };
        enum buttonNames {
            PlayButton
        };
    };
}// namespace screen

#endif// BATTLESHIP_HOMEPAGE_H