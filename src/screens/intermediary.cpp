/**
 * Front-end class that defines the behaviour of the Intermediary screens
 */

#include "intermediary.hpp"

using screen::Intermediary;

std::unique_ptr<Intermediary> Intermediary::instance = nullptr;

Intermediary &screen::Intermediary::getInstance() {
    if (instance == nullptr) {
        instance.reset(new Intermediary());
    }
    return *instance;
}

Intermediary::Intermediary() : ScreenTemplate() {
    const vector<string> texturePaths{"IntermediaryP1Background.png", "IntermediaryP2Background.png",
                                      "IdleContinueButton.png", "ActiveContinueButton.png"};
    this->resources = ScreenResourceManager("intermediary",texturePaths,
                                            {{sf::Vector2f(0, 0), sf::Vector2f(5, 5), textureNames::IntermediaryP1Background},
                                             {sf::Vector2f(0, 0), sf::Vector2f(5, 5), textureNames::IntermediaryP2Background}},
                                            {{sf::Vector2f(144 * 5, 108 * 5), sf::Vector2f(5, 5),
                                              textureNames::IdleContinueButton, textureNames::ActiveContinueButton}});
}

void Intermediary::update() {
    sf::Vector2f mousePosition = State::getMousePosition();
    resources.getButton(buttonNames::ContinueButton).updateButtonState(mousePosition);
}

void Intermediary::poll() {
    sf::RenderWindow &gui = *State::gui;
    sf::Event &event = State::event;

    while (gui.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                gui.close();
                break;
            case sf::Event::MouseButtonReleased:
                if (event.mouseButton.button == sf::Mouse::Left && resources.getButton(buttonNames::ContinueButton).getButtonState()) {
                    if (State::player == State::Player::P2 && State::getPreviousScreen() == Screens::FLEET_PLACEMENT) {
                        State::changeScreen(Screens::FLEET_PLACEMENT);
                        break;
                    } else {
                        State::changeScreen(Screens::GAMEPLAY);
                        break;
                    }
                }
            default:
                break;
        }
    }
}

void Intermediary::render() {
    sf::RenderWindow &gui = *State::gui;
    gui.clear();

    if (State::player == State::Player::P2) {
        gui.draw(resources.getSprite(spriteNames::BackgroundP2));
    } else {
        gui.draw(resources.getSprite(spriteNames::BackgroundP1));
    }
    resources.getButton(buttonNames::ContinueButton).render(gui);

    if (State::getCurrentScreen() == Screens::INTERMEDIARY) {
        gui.display();
    }
}
