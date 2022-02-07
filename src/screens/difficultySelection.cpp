/**
 * Front-end class that defines the behaviour of the Difficulty selection screens
 */

#include "difficultySelection.hpp"

using screen::DifficultySelection;

std::unique_ptr<DifficultySelection> DifficultySelection::instance = nullptr;

DifficultySelection::DifficultySelection() : ScreenTemplate() {
    const vector<string> texturePaths{"difficultySelection/DifficultyBackground.png",
                                      "difficultySelection/IdleEasyButton.png", "difficultySelection/ActiveEasyButton.png",
                                      "difficultySelection/IdleHardButton.png", "difficultySelection/ActiveHardButton.png",
                                      "difficultySelection/IdleBackButton.png", "difficultySelection/ActiveBackButton.png",
                                      "difficultySelection/IdleInstructionsButton.png", "difficultySelection/ActiveInstructionsButton.png"};
    const vector<sprite> sprites = {{sf::Vector2f(0, 0), sf::Vector2f(5, 5), Background_}};
    const vector<button> buttons = {{sf::Vector2f(88 * 5, 92 * 5), sf::Vector2f(5, 5), IdleEasyButton, ActiveEasyButton},
                                    {sf::Vector2f(200 * 5, 92 * 5), sf::Vector2f(5, 5), IdleHardButton, ActiveHardButton},
                                    {sf::Vector2f(320 * 5, 12 * 5), sf::Vector2f(5, 5), IdleBackButton, ActiveBackButton},
                                    {sf::Vector2f(352 * 5, 12 * 5), sf::Vector2f(5, 5), IdleInstructionsButton, ActiveInstructionsButton}};

    this->resources = ScreenResourceManager(texturePaths, sprites, buttons);
}

DifficultySelection &screen::DifficultySelection::getInstance() {
    if (instance == nullptr) {
        instance.reset(new DifficultySelection());
    }
    return *instance;
}

void DifficultySelection::update() {
    sf::Vector2f mousePosition = State::getMousePosition();

    resources.getButton(EasyButton).updateButtonState(mousePosition);
    resources.getButton(HardButton).updateButtonState(mousePosition);
    resources.getButton(BackButton).updateButtonState(mousePosition);
    resources.getButton(InstructionsButton).updateButtonState(mousePosition);
}

void DifficultySelection::poll() {
    sf::RenderWindow &gui = *State::gui;
    sf::Event &event = State::event;

    while (gui.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                gui.close();
                break;
            case sf::Event::MouseButtonReleased:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (resources.getButton(EasyButton).getButtonState()) {
                        State::difficulty = State::Difficulty::EASY;
                        State::changeScreen(Screens::FLEET_PLACEMENT);
                        break;
                    } else if (resources.getButton(HardButton).getButtonState()) {
                        State::difficulty = State::Difficulty::HARD;
                        State::changeScreen(Screens::FLEET_PLACEMENT);
                        break;
                    } else if (resources.getButton(BackButton).getButtonState()) {
                        State::changeScreen(Screens::GAME_MODE_SELECTION);
                        break;
                    } else if (resources.getButton(InstructionsButton).getButtonState()) {
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

void DifficultySelection::render() {
    sf::RenderWindow &gui = *State::gui;
    gui.clear();

    gui.draw(resources.getSprite(Background));
    resources.getButton(EasyButton).render(gui);
    resources.getButton(HardButton).render(gui);
    resources.getButton(BackButton).render(gui);
    resources.getButton(InstructionsButton).render(gui);

    if (State::getCurrentScreen() == Screens::DIFFICULTY_SELECTION) {
        gui.display();
    }
}
