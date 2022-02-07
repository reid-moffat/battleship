/**
 * Front-end class that defines the behaviour of the Game Mode selection screens
 */

#include "gameModeSelection.hpp"

using screen::GameModeSelection;

std::unique_ptr<GameModeSelection> GameModeSelection::instance = nullptr;

GameModeSelection::GameModeSelection() : ScreenTemplate() {
    const vector<string> texturePaths{"gameModeSelection/GameModeBackground.png",
                                      "gameModeSelection/Idle1PlayerButton.png", "gameModeSelection/Active1PlayerButton.png",
                                      "gameModeSelection/Idle2PlayerButton.png", "gameModeSelection/Active2PlayerButton.png",
                                      "gameModeSelection/IdleBackButton.png", "gameModeSelection/ActiveBackButton.png",
                                      "gameModeSelection/IdleInstructionsButton.png", "gameModeSelection/ActiveInstructionsButton.png"};
    const vector<sprite> sprites = {{sf::Vector2f(0, 0), sf::Vector2f(5, 5), Background_}};
    const vector<button> buttons = {{sf::Vector2f(88 * 5, 92 * 5), sf::Vector2f(5, 5), IdleOnePlayer, ActiveOnePlayer},
                                    {sf::Vector2f(200 * 5, 92 * 5), sf::Vector2f(5, 5), IdleTwoPlayer, ActiveTwoPlayer},
                                    {sf::Vector2f(320 * 5, 12 * 5), sf::Vector2f(5, 5), IdleBackButton, ActiveBackButton},
                                    {sf::Vector2f(352 * 5, 12 * 5), sf::Vector2f(5, 5), IdleInstructionsButton, ActiveInstructionsButton}};

    this->resources = ScreenResourceManager(texturePaths, sprites, buttons);
}

void GameModeSelection::update() {
    sf::Vector2f mousePosition = State::getMousePosition();

    resources.getButton(OnePlayer).updateButtonState(mousePosition);
    resources.getButton(TwoPlayers).updateButtonState(mousePosition);
    resources.getButton(Back).updateButtonState(mousePosition);
    resources.getButton(Instructions).updateButtonState(mousePosition);
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
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (resources.getButton(OnePlayer).getButtonState()) {
                        State::gameMode = State::GameMode::SINGLE_PLAYER;
                        State::changeScreen(Screens::DIFFICULTY_SELECTION);
                        break;
                    } else if (resources.getButton(TwoPlayers).getButtonState()) {
                        State::gameMode = State::GameMode::MULTI_PLAYER;
                        State::changeScreen(Screens::FLEET_PLACEMENT);
                        break;
                    } else if (resources.getButton(Back).getButtonState()) {
                        State::previousScreen();
                        break;
                    } else if (resources.getButton(Instructions).getButtonState()) {
                        State::changeScreen(Screens::INSTRUCTIONS);
                        break;
                    } else {
                        break;
                    }
                }
            default:
                break;
        }
    }
}

void GameModeSelection::render() {
    sf::RenderWindow &gui = *State::gui;
    gui.clear();

    gui.draw(resources.getSprite(Background));
    resources.getButton(OnePlayer).render(gui);
    resources.getButton(TwoPlayers).render(gui);
    resources.getButton(Back).render(gui);
    resources.getButton(Instructions).render(gui);

    if (State::getCurrentScreen() == Screens::GAME_MODE_SELECTION) {
        gui.display();
    }
}

GameModeSelection &screen::GameModeSelection::getInstance() {
    if (instance == nullptr) {
        instance.reset(new GameModeSelection());
    }
    return *instance;
}
