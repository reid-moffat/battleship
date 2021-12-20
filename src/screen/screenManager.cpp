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

    screenList[HOMEPAGE] = &Homepage::getInstance();
    screenList[INSTRUCTIONS] = &Instructions::getInstance();
    screenList[GAME_MODE_SELECTION] = &GameModeSelection::getInstance();
    screenList[DIFFICULTY_SELECTION] = &DifficultySelection::getInstance();
    screenList[FLEET_PLACEMENT] = &FleetPlacement::getInstance();
    screenList[GAMEPLAY] = &Gameplay::getInstance();
    screenList[INTERMEDIARY] = &Intermediary::getInstance();
    screenList[GAME_OVER] = &GameOver::getInstance();
}

void ScreenManager::run() {
    gui->setKeyRepeatEnabled(false);

    while (gui->isOpen()) {
        screenList[State::getCurrentScreen()]->run(*this->gui);
    }
}
