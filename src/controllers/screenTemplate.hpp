/**
 * Base abstract class that defines required functionality for screens
 */

#ifndef BATTLESHIP_SCREENTEMPLATE_H
#define BATTLESHIP_SCREENTEMPLATE_H

#include "state.hpp"

using std::map;

namespace screen {

    class ScreenTemplate {
    public:
        /**
         * Renders this screens to the GUI
         */
        virtual void run() = 0;

        /**
         * Copy constructor for heap memory
         */
        ScreenTemplate(const ScreenTemplate &other) = delete;

        /**
         * Assignment operator overriding
         */
        ScreenTemplate &operator=(const ScreenTemplate &rhs) = delete;

    protected:
        /**
         * Constructor for all children to call
         */
        ScreenTemplate();

        /**
         * Names to refer to the textures on this screen
         */
        enum class textureNames {};

        /**
         * All the textures for this screen, mapped to by their enumerated name
         */
        const map<textureNames, sf::Texture> textures;

        /**
         * Names to refer to the sprites on this screen
         */
        enum class spriteNames {};

        /**
         * All the sprites for this screen, mapped to by their enumerated name
         */
        const map<spriteNames, sf::Sprite> sprites;
    };

}// namespace screen

#endif// BATTLESHIP_SCREENTEMPLATE_H
