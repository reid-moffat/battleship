/**
 * File: homepage.cpp
 * Description: Front-end class that defines the behaviour of the Homepage screen
 */

#include "../../include/screen/homepage.h"

using screen::Homepage;

Homepage::Homepage() : ScreenTemplate() {
    State::loadTexture(this->homepageBackgroundTexture, "homepage/HomepageBackground.png");
    State::loadTexture(this->idlePlayButtonTexture, "homepage/IdlePlayButton.png");
    State::loadTexture(this->activePlayButtonTexture, "homepage/ActivePlayButton.png");

    State::setSprite(sf::Vector2f(0, 0), sf::Vector2f(5, 5), this->homepageBackgroundTexture, this->backgroundSprite);

    this->playButton = new Button(sf::Vector2f(232 * 5, 64 * 5), sf::Vector2f(5, 5), this->idlePlayButtonTexture, this->activePlayButtonTexture);
}

Homepage::Homepage(const Homepage &source) {
    this->homepageBackgroundTexture = source.homepageBackgroundTexture;
    this->idlePlayButtonTexture = source.idlePlayButtonTexture;
    this->activePlayButtonTexture = source.activePlayButtonTexture;
    this->backgroundSprite = source.backgroundSprite;
    this->mousePosition = source.mousePosition;
    this->event = source.event;
    this->playButton = new Button(*(source.playButton));
}

Homepage::~Homepage() {
    delete this->playButton;
    this->playButton = nullptr;
}

screen::Homepage &Homepage::operator=(const Homepage &source) {
    if (this == &source) {
        return *this;
    } else {
        this->homepageBackgroundTexture = source.homepageBackgroundTexture;
        this->idlePlayButtonTexture = source.idlePlayButtonTexture;
        this->activePlayButtonTexture = source.activePlayButtonTexture;
        this->backgroundSprite = source.backgroundSprite;
        this->mousePosition = source.mousePosition;
        this->event = source.event;
        this->playButton = source.playButton;
        return *this;
    }
}

void Homepage::update(sf::RenderWindow &gui, sf::Vector2f mousePosition) {
    State::updateMousePosition(gui, mousePosition);
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

void Homepage::run(sf::RenderWindow &gui) {
    this->update(gui, this->mousePosition);
    this->poll(gui);
    this->render(gui);
}