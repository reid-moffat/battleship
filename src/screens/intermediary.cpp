/**
 * File: intermediary.cpp
 * Description: Front-end class that defines the behaviour of the Intermediary screens
 */

#include "intermediary.hpp"
#include "helpers.hpp"

using screen::Intermediary;

Intermediary *Intermediary::instance = nullptr;

Intermediary::Intermediary() : ScreenTemplate() {
    loadTexture(this->intermediaryP1BackgroundTexture, "intermediary/IntermediaryP1Background.png");
    loadTexture(this->intermediaryP2BackgroundTexture, "intermediary/IntermediaryP2Background.png");
    loadTexture(this->idleContinueButtonTexture, "intermediary/IdleContinueButton.png");
    loadTexture(this->activeContinueButtonTexture, "intermediary/ActiveContinueButton.png");

    setSprite(sf::Vector2f(0, 0), sf::Vector2f(5, 5), this->intermediaryP1BackgroundTexture, this->backgroundP1Sprite);
    setSprite(sf::Vector2f(0, 0), sf::Vector2f(5, 5), this->intermediaryP2BackgroundTexture, this->backgroundP2Sprite);

    this->continueButton = new Button(sf::Vector2f(144 * 5, 108 * 5), sf::Vector2f(5, 5), this->idleContinueButtonTexture, this->activeContinueButtonTexture);
}

void Intermediary::update(sf::RenderWindow &gui, sf::Vector2f mousePos) {
    updateMousePosition(gui, mousePos);
    this->continueButton->updateButtonState(mousePos);
}

void Intermediary::poll(sf::RenderWindow &gui) {
    while (gui.pollEvent(this->event)) {
        switch (this->event.type) {

            case sf::Event::Closed:
                gui.close();
                break;

            case sf::Event::MouseButtonReleased:
                if ((event.mouseButton.button == sf::Mouse::Left) && (this->continueButton->getButtonState())) {
                    if ((State::player == State::Player::P2) && (State::getPreviousScreen() == Screens::FLEET_PLACEMENT)) {
                        State::changeScreen(Screens::FLEET_PLACEMENT);
                        break;
                    } else if ((State::player == State::Player::P1) && (State::getPreviousScreen() == Screens::FLEET_PLACEMENT)) {
                        State::changeScreen(Screens::GAMEPLAY);
                        break;
                    } else if ((State::player == State::Player::P2) && (State::getPreviousScreen() == Screens::GAMEPLAY)) {
                        State::changeScreen(Screens::GAMEPLAY);
                        break;
                    } else if ((State::player == State::Player::P1) && (State::getPreviousScreen() == Screens::GAMEPLAY)) {
                        State::changeScreen(Screens::GAMEPLAY);
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

void Intermediary::render(sf::RenderWindow &gui) {
    gui.clear();

    if (State::player == State::Player::P2) {
        gui.draw(this->backgroundP2Sprite);
    } else {
        gui.draw(this->backgroundP1Sprite);
    }
    continueButton->render(gui);

    if (State::getCurrentScreen() == Screens::INTERMEDIARY) {
        gui.display();
    }
}

void Intermediary::run() {
    this->update(*State::gui, this->mousePosition);
    this->poll(*State::gui);
    this->render(*State::gui);
}

Intermediary &screen::Intermediary::getInstance() {
    if (instance == nullptr) {
        instance = new Intermediary();
    }
    return *instance;
}
