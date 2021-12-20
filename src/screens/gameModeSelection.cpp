/**
 * File: gameModeSelection.cpp
 * Description: Front-end class that defines the behaviour of the Game Mode selection screens
 */

#include "gameModeSelection.hpp"
#include "../helpers.hpp"

using screen::GameModeSelection;

GameModeSelection *GameModeSelection::instance = nullptr;

GameModeSelection::GameModeSelection() : ScreenTemplate() {
    loadTexture(this->gameModeBackgroundTexture, "gameModeSelection/GameModeBackground.png");
    loadTexture(this->idleOnePlayerButtonTexture, "gameModeSelection/Idle1PlayerButton.png");
    loadTexture(this->activeOnePlayerButtonTexture, "gameModeSelection/Active1PlayerButton.png");
    loadTexture(this->idleTwoPlayerButtonTexture, "gameModeSelection/Idle2PlayerButton.png");
    loadTexture(this->activeTwoPlayerButtonTexture, "gameModeSelection/Active2PlayerButton.png");
    loadTexture(this->idleBackButtonTexture, "gameModeSelection/IdleBackButton.png");
    loadTexture(this->activeBackButtonTexture, "gameModeSelection/ActiveBackButton.png");
    loadTexture(this->idleInstructionsButtonTexture, "gameModeSelection/IdleInstructionsButton.png");
    loadTexture(this->activeInstructionsButtonTexture, "gameModeSelection/ActiveInstructionsButton.png");

    setSprite(sf::Vector2f(0, 0), sf::Vector2f(5, 5), this->gameModeBackgroundTexture, this->backgroundSprite);

    this->onePlayerButton = new Button(sf::Vector2f(88 * 5, 92 * 5), sf::Vector2f(5, 5), this->idleOnePlayerButtonTexture, this->activeOnePlayerButtonTexture);
    this->twoPlayerButton = new Button(sf::Vector2f(200 * 5, 92 * 5), sf::Vector2f(5, 5), this->idleTwoPlayerButtonTexture, this->activeTwoPlayerButtonTexture);
    this->backButton = new Button(sf::Vector2f(320 * 5, 12 * 5), sf::Vector2f(5, 5), this->idleBackButtonTexture, this->activeBackButtonTexture);
    this->instructionsButton = new Button(sf::Vector2f(352 * 5, 12 * 5), sf::Vector2f(5, 5), this->idleInstructionsButtonTexture, this->activeInstructionsButtonTexture);
}

void GameModeSelection::update(sf::RenderWindow &gui, sf::Vector2f mousePosition) {
    updateMousePosition(gui, mousePosition);
    this->onePlayerButton->updateButtonState(mousePosition);
    this->twoPlayerButton->updateButtonState(mousePosition);
    this->backButton->updateButtonState(mousePosition);
    this->instructionsButton->updateButtonState(mousePosition);
}

void GameModeSelection::poll(sf::RenderWindow &gui) {
    while (gui.pollEvent(this->event)) {
        switch (this->event.type) {

            case sf::Event::Closed:
                gui.close();
                break;

            case sf::Event::MouseButtonReleased:
                if ((event.mouseButton.button == sf::Mouse::Left) && (this->onePlayerButton->getButtonState())) {
                    State::gameMode = State::GameMode::SINGLE_PLAYER;
                    State::changeScreen(Screens::DIFFICULTY_SELECTION);
                    break;
                } else if ((event.mouseButton.button == sf::Mouse::Left) && (this->twoPlayerButton->getButtonState())) {
                    State::gameMode = State::GameMode::MULTI_PLAYER;
                    State::changeScreen(Screens::FLEET_PLACEMENT);
                    break;
                } else if ((event.mouseButton.button == sf::Mouse::Left) && (this->backButton->getButtonState())) {
                    State::previousScreen();
                    break;
                } else if ((event.mouseButton.button == sf::Mouse::Left) && (this->instructionsButton->getButtonState())) {
                    State::changeScreen(Screens::INSTRUCTIONS);
                    break;
                } else {
                    break;
                }

            default:
                break;
        }
    }
}

void GameModeSelection::render(sf::RenderWindow &gui) {
    gui.clear();

    gui.draw(this->backgroundSprite);
    onePlayerButton->render(gui);
    twoPlayerButton->render(gui);
    backButton->render(gui);
    instructionsButton->render(gui);

    if (State::getCurrentScreen() == Screens::GAME_MODE_SELECTION) {
        gui.display();
    }
}

void GameModeSelection::run() {
    this->update(*State::gui, this->mousePosition);
    this->poll(*State::gui);
    this->render(*State::gui);
}

GameModeSelection &screen::GameModeSelection::getInstance() {
    if (instance == nullptr) {
        instance = new GameModeSelection();
    }
    return *instance;
}
