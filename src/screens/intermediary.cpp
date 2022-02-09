/**
 * Front-end class that defines the behaviour of the Intermediary screens
 */

#include "intermediary.hpp"

using screen::Intermediary;

std::unique_ptr<class Intermediary> Intermediary::instance = nullptr;

Intermediary::Intermediary() : ScreenTemplate() {
    // Data required for all the SFML objects on this screen
    const vector<string> texturePaths{
            "IntermediaryP1Background.png",
            "IntermediaryP2Background.png",
            "IdleContinueButton.png",
            "ActiveContinueButton.png",
    };
    const vector<sprite> sprites = {
            {sf::Vector2f(0, 0), sf::Vector2f(5, 5), IntermediaryP1BackgroundTexture},
            {sf::Vector2f(0, 0), sf::Vector2f(5, 5), IntermediaryP2BackgroundTexture},
    };
    const vector<button> buttons = {
            {sf::Vector2f(144 * 5, 108 * 5), sf::Vector2f(5, 5), IdleContinueButtonTexture, ActiveContinueButtonTexture},
    };

    // Initialize SFML objects
    this->resources = ScreenResourceManager("intermediary", texturePaths, sprites, buttons);
}

class Intermediary &screen::Intermediary::getInstance() {
    if (instance == nullptr) {
        instance.reset(new Intermediary());
    }
    return *instance;
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
                    if (State::player == State::Player::P2 && State::getPreviousScreen() == Screens::FleetPlacement) {
                        State::changeScreen(Screens::FleetPlacement);
                    } else {
                        State::changeScreen(Screens::Gameplay);
                    }
                }
                break;
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

    gui.display();
}
