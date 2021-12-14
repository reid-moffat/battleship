/**
 * File: intermediary.cpp
 * Description: Front-end class that defines the behaviour of the Intermediary screen
 */

#include "../../include/screen/intermediary.h"

using screen::Intermediary;

Intermediary::Intermediary() : ScreenTemplate() {
    State::loadTexture(this->intermediaryP1BackgroundTexture, "intermediary/IntermediaryP1Background.png");
    State::loadTexture(this->intermediaryP2BackgroundTexture, "intermediary/IntermediaryP2Background.png");
    State::loadTexture(this->idleContinueButtonTexture, "intermediary/IdleContinueButton.png");
    State::loadTexture(this->activeContinueButtonTexture, "intermediary/ActiveContinueButton.png");

    State::setSprite(sf::Vector2f(0, 0), sf::Vector2f(5, 5), this->intermediaryP1BackgroundTexture, this->backgroundP1Sprite);
    State::setSprite(sf::Vector2f(0, 0), sf::Vector2f(5, 5), this->intermediaryP2BackgroundTexture, this->backgroundP2Sprite);

    this->continueButton = new Button(sf::Vector2f(144 * 5, 108 * 5), sf::Vector2f(5, 5), this->idleContinueButtonTexture, this->activeContinueButtonTexture);
}

Intermediary::Intermediary(const Intermediary &source) {
    this->intermediaryP1BackgroundTexture = source.intermediaryP1BackgroundTexture;
    this->intermediaryP2BackgroundTexture = source.intermediaryP2BackgroundTexture;
    this->idleContinueButtonTexture = source.idleContinueButtonTexture;
    this->activeContinueButtonTexture = source.activeContinueButtonTexture;
    this->backgroundP1Sprite = source.backgroundP1Sprite;
    this->backgroundP2Sprite = source.backgroundP2Sprite;
    this->mousePosition = source.mousePosition;
    this->event = source.event;
    this->continueButton = new Button(*(source.continueButton));
}

Intermediary::~Intermediary() {
    delete this->continueButton;
    this->continueButton = nullptr;
}

screen::Intermediary &Intermediary::operator=(const Intermediary &source) {
    if (this == &source) {
        return *this;
    } else {
        this->intermediaryP1BackgroundTexture = source.intermediaryP1BackgroundTexture;
        this->intermediaryP2BackgroundTexture = source.intermediaryP2BackgroundTexture;
        this->idleContinueButtonTexture = source.idleContinueButtonTexture;
        this->activeContinueButtonTexture = source.activeContinueButtonTexture;
        this->backgroundP1Sprite = source.backgroundP1Sprite;
        this->backgroundP2Sprite = source.backgroundP2Sprite;
        this->event = source.event;
        this->continueButton = source.continueButton;
        return *this;
    }
}

void Intermediary::update(sf::RenderWindow &gui, sf::Vector2f mousePosition) {
    State::updateMousePosition(gui, mousePosition);
    this->continueButton->updateButtonState(mousePosition);
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

void Intermediary::run(sf::RenderWindow &gui) {
    this->update(gui, this->mousePosition);
    this->poll(gui);
    this->render(gui);
}