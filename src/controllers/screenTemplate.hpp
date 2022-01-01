/**
 * Base abstract class that defines required functionality for screens
 */

#ifndef BATTLESHIP_SCREENTEMPLATE_H
#define BATTLESHIP_SCREENTEMPLATE_H

#include "../helpers/ImagesManager.hpp"
#include "state.hpp"
#include <SFML/System.hpp>

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
         * All the textures and sprites for this screen
         */
        ImagesManager images;
    };

}// namespace screen

#endif// BATTLESHIP_SCREENTEMPLATE_H
