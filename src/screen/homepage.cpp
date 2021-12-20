/**
 * File: homepage.cpp
 * Description: Front-end class that defines the behaviour of the Homepage screen
 */

#include "../../include/screen/homepage.hpp"
#include "../../include/helpers/helpers.hpp"

using screen::Homepage;

Homepage* Homepage::instance = nullptr;

Homepage &screen::Homepage::getInstance() {
    if (instance == nullptr) {
        instance = new Homepage();
    }
    return *instance;
}

void Homepage::run() {
    this->update(*State::gui, this->mousePosition);
    this->poll(*State::gui);
    this->render(*State::gui);
}

Homepage::Homepage() {
    loadTexture(this->homepageBackgroundTexture, "homepage/HomepageBackground.png");
    loadTexture(this->idlePlayButtonTexture, "homepage/IdlePlayButton.png");
    loadTexture(this->activePlayButtonTexture, "homepage/ActivePlayButton.png");

    setSprite(sf::Vector2f(0, 0), sf::Vector2f(5, 5), this->homepageBackgroundTexture, this->backgroundSprite);

    this->playButton = new Button(sf::Vector2f(232 * 5, 64 * 5), sf::Vector2f(5, 5), this->idlePlayButtonTexture, this->activePlayButtonTexture);
}

void Homepage::update(sf::RenderWindow &gui, sf::Vector2f mousePosition) {
    updateMousePosition(gui, mousePosition);
    this->playButton->updateButtonState(mousePosition);
}

void Homepage::poll(sf::RenderWindow &gui) {
    while (gui.pollEvent(this->event)) {
        switch (this->event.type) {

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

void Homepage::render(sf::RenderWindow &gui) {
    gui.clear();

    gui.draw(this->backgroundSprite);
    playButton->render(gui);

    if (State::getCurrentScreen() == Screens::HOMEPAGE) {
        gui.display();
    }
}
