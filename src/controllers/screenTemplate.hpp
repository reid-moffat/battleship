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
         * Renders this screen to the GUI
         */
        void run();

        // Do not allow copying of this screen's instance
        ScreenTemplate(const ScreenTemplate &other) = delete;

        // Do not allow assignment of this screen's instance
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

        // Place any code needed to update objects before pooling and rendering here
        // such as checking if the mouse is above a button
        virtual void update() = 0;

        // Pool for events. Make sure to poll for if the user clicks the X button on the window
        virtual void poll() = 0;

        // Render all sprites to the screen here
        virtual void render() = 0;
    };

}// namespace screen

#endif// BATTLESHIP_SCREENTEMPLATE_H
