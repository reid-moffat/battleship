/**
 * Base abstract class that defines required functionality for screens
 */

#ifndef BATTLESHIP_SCREENTEMPLATE_H
#define BATTLESHIP_SCREENTEMPLATE_H

#include "../helpers/ScreenResourceManager.hpp"
#include "state.hpp"

using std::map;

namespace screen {

    class ScreenTemplate {
    public:
        /**
         * Renders this screens to the GUI
         */
        void run();

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
        ScreenResourceManager resources;

        /**
         *
         */
        virtual void update() = 0;

        /**
         *
         */
        virtual void poll() = 0;

        /**
         *
         */
        virtual void render() = 0;
    };

}// namespace screen

#endif// BATTLESHIP_SCREENTEMPLATE_H
