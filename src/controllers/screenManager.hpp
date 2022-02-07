/**
 * Top-level class for managing the user interface
 * To run battleship, instantiate this class and call run()
 */

#ifndef BATTLESHIP_SCREENMANAGER_H
#define BATTLESHIP_SCREENMANAGER_H

#include "../controllers/screenTemplate.hpp"
#include "state.hpp"
#include <map>

namespace screen {
    class ScreenManager {
    public:
        /**
         * Instantiates this class
         */
        ScreenManager();

        /**
         * Runs the game
         */
        void run();

    private:
        /**
         * All of the different screens instances, mapped to by their name
         */
        std::map<Screens, ScreenTemplate *> screenList;
    };
}// namespace screen

#endif// BATTLESHIP_SCREENMANAGER_H
