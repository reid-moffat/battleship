/**
 * File: instructions.cpp
 * Description: Front-end class that defines the behaviour of the Instructions screens
 */

#include "instructions.hpp"
#include "../helpers.hpp"

using screen::Instructions;

Instructions *Instructions::instance = nullptr;

Instructions::Instructions() : ScreenTemplate() {
    loadTexture(this->instructionsBackgroundTexture, "instructions/InstructionsBackground.png");
    loadTexture(this->idleBackButtonTexture, "instructions/IdleBackButton.png");
    loadTexture(this->activeBackButtonTexture, "instructions/ActiveBackButton.png");

    setSprite(sf::Vector2f(0, 0), sf::Vector2f(5, 5), this->instructionsBackgroundTexture, this->backgroundSprite);

    this->backButton = new Button(sf::Vector2f(352 * 5, 12 * 5), sf::Vector2f(5, 5), this->idleBackButtonTexture, this->activeBackButtonTexture);
}

void Instructions::update(sf::RenderWindow &gui, sf::Vector2f mousePosition) {
    updateMousePosition(gui, mousePosition);
    this->backButton->updateButtonState(mousePosition);
}

void Instructions::poll(sf::RenderWindow &gui) {
    while (gui.pollEvent(this->event)) {
        switch (this->event.type) {

            case sf::Event::Closed:
                gui.close();
                break;

            case sf::Event::MouseButtonReleased:
                if ((event.mouseButton.button == sf::Mouse::Left) && (this->backButton->getButtonState())) {
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

void Instructions::render(sf::RenderWindow &gui) {
    gui.clear();

    gui.draw(this->backgroundSprite);
    backButton->render(gui);

    if (State::getCurrentScreen() == Screens::INSTRUCTIONS) {
        gui.display();
    }
}

void Instructions::run() {
    this->update(*State::gui, this->mousePosition);
    this->poll(*State::gui);
    this->render(*State::gui);
}

Instructions &screen::Instructions::getInstance() {
    if (instance == nullptr) {
        instance = new Instructions;
    }
    return *instance;
}