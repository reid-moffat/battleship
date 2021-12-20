/**
 * ScreenManager class implementation
 */

#include "../../include/screen/screenManager.hpp"
#include "../../include/screen/difficultySelection.hpp"
#include "../../include/screen/fleetPlacement.hpp"
#include "../../include/screen/gameModeSelection.hpp"
#include "../../include/screen/gameOver.hpp"
#include "../../include/screen/gameplay.hpp"
#include "../../include/screen/homepage.hpp"
#include "../../include/screen/instructions.hpp"
#include "../../include/screen/intermediary.hpp"

using screen::ScreenManager;
using screen::Screens;

ScreenManager::ScreenManager() {
    this->gui = new sf::RenderWindow(sf::VideoMode(State::width, State::height), "Battleship", sf::Style::Titlebar | sf::Style::Close);
    this->gui->setFramerateLimit(60);
}

void ScreenManager::run() {
    gui->setKeyRepeatEnabled(false);

    while (gui->isOpen()) {
        switch (State::getCurrentScreen()) {
            case HOMEPAGE:
                Homepage::getInstance().run(*this->gui);
                break;
            case INSTRUCTIONS:
                Instructions::getInstance().run(*this->gui);
                break;
            case GAME_MODE_SELECTION:
                GameModeSelection::getInstance().run(*this->gui);
                break;
            case DIFFICULTY_SELECTION:
                DifficultySelection::getInstance().run(*this->gui);
                break;
            case FLEET_PLACEMENT:
                FleetPlacement::getInstance().run(*this->gui);
                break;
            case GAMEPLAY:
                Gameplay::getInstance().run(*this->gui);
                break;
            case INTERMEDIARY:
                Intermediary::getInstance().run(*this->gui);
                break;
            case GAME_OVER:
                GameOver::getInstance().run(*this->gui);
                break;
        }
    }
}
