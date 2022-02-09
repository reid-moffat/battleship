/**
 * Front-end class that defines the behaviour of the Game Mode selection screens
 */

#include "gameModeSelection.hpp"

using screen::GameModeSelection;

std::unique_ptr<class GameModeSelection> GameModeSelection::instance = nullptr;

GameModeSelection::GameModeSelection() : ScreenTemplate() {
    // Data required for all the SFML objects on this screen
    const vector<string> texturePaths{
            "GameModeBackground.png",

            "Idle1PlayerButton.png",
            "Active1PlayerButton.png",
            "Idle2PlayerButton.png",
            "Active2PlayerButton.png",
            "IdleBackButton.png",
            "ActiveBackButton.png",
            "IdleInstructionsButton.png",
            "ActiveInstructionsButton.png",
    };
    const vector<sprite> sprites = {
            {sf::Vector2f(0, 0), sf::Vector2f(5, 5), Background_},
    };
    const vector<button> buttons = {
            {sf::Vector2f(88 * 5, 92 * 5), sf::Vector2f(5, 5), IdleOnePlayerButtonTexture, ActiveOnePlayerButtonTexture},
            {sf::Vector2f(200 * 5, 92 * 5), sf::Vector2f(5, 5), IdleTwoPlayerButtonTexture, ActiveTwoPlayerButtonTexture},
            {sf::Vector2f(320 * 5, 12 * 5), sf::Vector2f(5, 5), IdleBackButtonTexture, ActiveBackButtonTexture},
            {sf::Vector2f(352 * 5, 12 * 5), sf::Vector2f(5, 5), IdleInstructionsButtonTexture, ActiveInstructionsButtonTexture},
    };

    // Initialize SFML objects
    this->resources = ScreenResourceManager("gameModeSelection", texturePaths, sprites, buttons);
}

class GameModeSelection &screen::GameModeSelection::getInstance() {
    if (instance == nullptr) {
        instance.reset(new GameModeSelection());
    }
    return *instance;
}

void GameModeSelection::update() {
    sf::Vector2f mousePosition = State::getMousePosition();

    // Update every button's state
    for (int i = OnePlayer; i <= Instructions; ++i) {
        resources.getButton(i).updateButtonState(mousePosition);
    }
}

void GameModeSelection::poll() {
    sf::RenderWindow &gui = *State::gui;
    sf::Event &event = State::event;

    while (gui.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                gui.close();
                break;
            case sf::Event::MouseButtonReleased:
                if (event.mouseButton.button != sf::Mouse::Left) break;

                if (resources.getButton(OnePlayer).getButtonState()) {
                    State::gameMode = State::GameMode::SINGLE_PLAYER;
                    State::changeScreen(Screens::DifficultySelection);
                } else if (resources.getButton(TwoPlayers).getButtonState()) {
                    State::gameMode = State::GameMode::MULTI_PLAYER;
                    State::changeScreen(Screens::FleetPlacement);
                } else if (resources.getButton(Back).getButtonState()) {
                    State::previousScreen();
                } else if (resources.getButton(Instructions).getButtonState()) {
                    State::changeScreen(Screens::Instructions);
                }
                break;
            default:
                break;
        }
    }
}

void GameModeSelection::render() {
    sf::RenderWindow &gui = *State::gui;
    gui.clear();

    gui.draw(resources.getSprite(Background));
    for (int i = OnePlayer; i <= Instructions; ++i) {
        resources.getButton(i).render(gui);
    }

    gui.display();
}
