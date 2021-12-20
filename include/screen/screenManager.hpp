/**
* Top-level class for managing the user interface
* To run battleship, instantiate this class and call run()
*
*/

#ifndef BATTLESHIP_SCREENMANAGER_H
#define BATTLESHIP_SCREENMANAGER_H

#include "../state.hpp"
#include "screenTemplate.hpp"

#include <map>

namespace screen {
    class ScreenManager {
    private:
        /**
        * All of the different screens, mapped to by their name
        */
        std::map<Screens, ScreenTemplate&> screenList;

        /**
        * SFML window for rendering
        */
        sf::RenderWindow *gui;

    public:
        /**
        * Instantiates this class
        */
        ScreenManager();

        /**
        * Runs the game
        */
        void run();
    };
}// namespace screen

#endif// BATTLESHIP_SCREENMANAGER_H
