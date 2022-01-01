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

void Homepage::run() {
    this->update();
    this->poll();
    this->render();
}

Homepage::Homepage() {
    const vector<string> texturePaths{"homepage/HomepageBackground.png", "homepage/IdlePlayButton.png", "homepage/ActivePlayButton.png"};
    this->images = ImagesManager(texturePaths, {{sf::Vector2f(0, 0), sf::Vector2f(5, 5), textureNames::Background}});

    this->playButton = std::make_unique<Button>(sf::Vector2f(232 * 5, 64 * 5), sf::Vector2f(5, 5),
                                                images.getTexture(textureNames::IdlePlayButton),
                                                images.getTexture(textureNames::ActivePlayButton));
}

void Homepage::update() {
    sf::Vector2f mousePosition = State::getMousePosition();
    this->playButton->updateButtonState(mousePosition);
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
                if ((event.mouseButton.button == sf::Mouse::Left) && (this->playButton->getButtonState())) {
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

    gui.draw(images.getSprite(spriteNames::Backgrounds));
    playButton->render(gui);

    if (State::getCurrentScreen() == Screens::HOMEPAGE) {
        gui.display();
    }
}
