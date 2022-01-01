/**
 * ScreenManager class implementation
 */

#include "screenManager.hpp"

#include "../screens/difficultySelection.hpp"
#include "../screens/fleetPlacement.hpp"
#include "../screens/gameModeSelection.hpp"
#include "../screens/gameOver.hpp"
#include "../screens/gameplay.hpp"
#include "../screens/homepage.hpp"
#include "../screens/instructions.hpp"
#include "../screens/intermediary.hpp"

using screen::ScreenManager;
using screen::Screens;

ScreenManager::ScreenManager() {
    State::gui = std::make_unique<sf::RenderWindow>(sf::VideoMode(State::width, State::height), "Battleship", sf::Style::Titlebar | sf::Style::Close);
    State::gui->setFramerateLimit(60);

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
    State::gui->setKeyRepeatEnabled(false);

    while (State::gui->isOpen()) {
        screenList[State::getCurrentScreen()]->run();
    }
}
