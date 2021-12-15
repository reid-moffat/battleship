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

    screenList[HOMEPAGE] = new Homepage();
    screenList[INSTRUCTIONS] = new Instructions();
    screenList[GAME_MODE_SELECTION] = new GameModeSelection();
    screenList[DIFFICULTY_SELECTION] = new DifficultySelection();
    screenList[FLEET_PLACEMENT] = new FleetPlacement();
    screenList[INTERMEDIARY] = new Intermediary();
    screenList[GAMEPLAY] = new Gameplay();
    screenList[GAME_OVER] = new GameOver();
};

void ScreenManager::run() {
    gui->setKeyRepeatEnabled(false);

    while (gui->isOpen()) {
        this->screenList[State::getCurrentScreen()]->run(*this->gui);
    }
}
