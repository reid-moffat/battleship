/**
* Base class that provides required functionality for screens
*/

#ifndef BATTLESHIP_SCREENTEMPLATE_H
#define BATTLESHIP_SCREENTEMPLATE_H

#include "../state.h"

namespace screen {

    class ScreenTemplate {
    protected:
        /**
        * Constructor for all children to call
        */
        ScreenTemplate();

        /**
        * Copy constructor for heap memory
        */
        ScreenTemplate(const ScreenTemplate &other);

        /**
        * Destructor for heap memory
        */
        virtual ~ScreenTemplate() = 0;

    public:
        /**
        * Renders this screen to the GUI
        */
        virtual void run(sf::RenderWindow &gui) = 0;

        /**
        * Assignment operator overriding
        */
        ScreenTemplate &operator=(const ScreenTemplate &rhs);
    };

}// namespace screen

#endif// BATTLESHIP_SCREENTEMPLATE_H
