/**
 * Description: Front-end class that defines the behaviour of the Homepage screens
 */

#include "homepage.hpp"
#include <memory>

using screen::Homepage;
using std::vector;

std::unique_ptr<Homepage> Homepage::instance = nullptr;

Homepage &Homepage::getInstance() {
    if (instance == nullptr) {
        instance.reset(new Homepage());
    }
    return *instance;
}

Homepage::Homepage() {
    const vector<string> texturePaths{"homepage/HomepageBackground.png", "homepage/IdlePlayButton.png", "homepage/ActivePlayButton.png"};
    this->resources = ScreenResourceManager(texturePaths,
                                            {{sf::Vector2f(0, 0), sf::Vector2f(5, 5), textureNames::Background}},
                                            {{sf::Vector2f(232 * 5, 64 * 5), sf::Vector2f(5, 5),
                                              textureNames::IdlePlayButton, textureNames::ActivePlayButton}});
}

void Homepage::update() {
    sf::Vector2f mousePosition = State::getMousePosition();
    resources.getButton(buttonNames::PlayButton).updateButtonState(mousePosition);
}

void Homepage::poll() {
    sf::RenderWindow &gui = *State::gui;
    sf::Event &event = State::event;

    while (gui.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                gui.close();
                break;
            case sf::Event::MouseButtonReleased:
                if ((event.mouseButton.button == sf::Mouse::Left) && (resources.getButton(buttonNames::PlayButton).getButtonState())) {
                    State::changeScreen(Screens::GAME_MODE_SELECTION);
                    break;
                } else {
                    break;
                }
            default:
                break;
        }
    }
}

void Homepage::render() {
    sf::RenderWindow &gui = *State::gui;
    gui.clear();

    gui.draw(resources.getSprite(spriteNames::Backgrounds));
    resources.getButton(buttonNames::PlayButton).render(gui);

    if (State::getCurrentScreen() == Screens::HOMEPAGE) {
        gui.display();
    }
}
