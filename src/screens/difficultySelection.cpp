/**
 * Front-end class that defines the behaviour of the Difficulty selection screens
 */

#include "difficultySelection.hpp"

using screen::DifficultySelection;

std::unique_ptr<class DifficultySelection> DifficultySelection::instance = nullptr;

DifficultySelection::DifficultySelection() : ScreenTemplate() {
    // Data required for all the SFML objects on this screen
    const vector<string> texturePaths = {
            "DifficultyBackground.png", // Background

            "IdleEasyButton.png", // Buttons
            "ActiveEasyButton.png",
            "IdleHardButton.png",
            "ActiveHardButton.png",
            "IdleBackButton.png",
            "ActiveBackButton.png",
            "IdleInstructionsButton.png",
            "ActiveInstructionsButton.png",
    };
    const vector<sprite> sprites = {
            {sf::Vector2f(0, 0), sf::Vector2f(5, 5), BackgroundTexture},
    };
    const vector<button> buttons = {
            {sf::Vector2f(88 * 5, 92 * 5), sf::Vector2f(5, 5), IdleEasyButtonTexture, ActiveEasyButtonTexture},
            {sf::Vector2f(200 * 5, 92 * 5), sf::Vector2f(5, 5), IdleHardButtonTexture, ActiveHardButtonTexture},
            {sf::Vector2f(320 * 5, 12 * 5), sf::Vector2f(5, 5), IdleBackButtonTexture, ActiveBackButtonTexture},
            {sf::Vector2f(352 * 5, 12 * 5), sf::Vector2f(5, 5), IdleInstructionsButtonTexture, ActiveInstructionsButtonTexture},
    };

    // Initialize SFML objects
    this->resources = ScreenResourceManager("difficultySelection", texturePaths, sprites, buttons);
}

class DifficultySelection &screen::DifficultySelection::getInstance() {
    if (instance == nullptr) {
        instance.reset(new DifficultySelection());
    }
    return *instance;
}

void DifficultySelection::update() {
    const sf::Vector2f mousePosition = State::getMousePosition();

    // Update every button's state
    for (int i = EasyButton; i <= InstructionsButton; ++i) {
        resources.getButton(i).updateButtonState(mousePosition);
    }
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
                        State::changeScreen(Screens::FleetPlacement);
                    } else if (resources.getButton(HardButton).getButtonState()) {
                        State::difficulty = State::Difficulty::HARD;
                        State::changeScreen(Screens::FleetPlacement);
                    } else if (resources.getButton(BackButton).getButtonState()) {
                        State::changeScreen(Screens::GameModeSelection);
                    } else if (resources.getButton(InstructionsButton).getButtonState()) {
                        State::changeScreen(Screens::Instructions);
                    }
                    break;
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
    for (int i = EasyButton; i <= InstructionsButton; ++i) {
        resources.getButton(i).render(gui);
    }

    gui.display();
}
