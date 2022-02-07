/**
 * File: instructions.cpp
 * Description: Front-end class that defines the behaviour of the Instructions screens
 */

#include "instructions.hpp"

using screen::Instructions;

std::unique_ptr<Instructions> Instructions::instance = nullptr;

Instructions &screen::Instructions::getInstance() {
    if (instance == nullptr) {
        instance.reset(new Instructions);
    }
    return *instance;
}

Instructions::Instructions() : ScreenTemplate() {
    const vector<string> texturePaths{"InstructionsBackground.png", "IdleBackButton.png", "ActiveBackButton.png"};
    this->resources = ScreenResourceManager("instructions",texturePaths,
                                            {{sf::Vector2f(0, 0), sf::Vector2f(5, 5), textureNames::Background_}},
                                            {{sf::Vector2f(352 * 5, 12 * 5), sf::Vector2f(5, 5),
                                              textureNames::IdleBackButton, textureNames::ActiveBackButton}});
}

void Instructions::update() {
    sf::Vector2f mousePosition = State::getMousePosition();
    resources.getButton(buttonNames::BackButton).updateButtonState(mousePosition);
}

void Instructions::poll() {
    sf::RenderWindow &gui = *State::gui;
    sf::Event &event = State::event;

    while (gui.pollEvent(event)) {
        switch (event.type) {

            case sf::Event::Closed:
                gui.close();
                break;

            case sf::Event::MouseButtonReleased:
                if (event.mouseButton.button == sf::Mouse::Left && resources.getButton(buttonNames::BackButton).getButtonState()) {
                    State::previousScreen();
                    break;
                } else {
                    break;
                }

            default:
                break;
        }
    }
}

void Instructions::render() {
    sf::RenderWindow &gui = *State::gui;
    gui.clear();

    gui.draw(resources.getSprite(spriteNames::Background));
    resources.getButton(buttonNames::BackButton).render(gui);

    if (State::getCurrentScreen() == Screens::INSTRUCTIONS) {
        gui.display();
    }
}
