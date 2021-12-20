/**
 * Base abstract class that defines required functionality for screens
 */

#ifndef BATTLESHIP_SCREENTEMPLATE_H
#define BATTLESHIP_SCREENTEMPLATE_H

#include "state.hpp"

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
    };

}// namespace screens

#endif// BATTLESHIP_SCREENTEMPLATE_H
