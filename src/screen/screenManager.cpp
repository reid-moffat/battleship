/**
 * ScreenManager class implementation
 */

#include "../../include/screen/screenManager.h"
#include "../../include/screen/difficultySelection.h"
#include "../../include/screen/fleetPlacement.h"
#include "../../include/screen/gameModeSelection.h"
#include "../../include/screen/gameOver.h"
#include "../../include/screen/gameplay.h"
#include "../../include/screen/homepage.h"
#include "../../include/screen/instructions.h"
#include "../../include/screen/intermediary.h"

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
