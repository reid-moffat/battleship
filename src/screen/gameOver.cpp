/**
 * File: gameOver.cpp
 * Description: Front-end class that defines the behaviour of the Game Over screen
 */

#include "../../include/screen/gameOver.h"
#include "../../include/helpers/sprites.h"
#include "../../include/helpers/userInput.h"

using screen::GameOver;

GameOver::GameOver() : ScreenTemplate() {
    loadTexture(this->gameOverWinBackgroundTexture, "gameOver/GameOverWinBackground.png");
    loadTexture(this->gameOverLoseBackgroundTexture, "gameOver/GameOverLoseBackground.png");
    loadTexture(this->gameOverP1BackgroundTexture, "gameOver/GameOverP1Background.png");
    loadTexture(this->gameOverP2BackgroundTexture, "gameOver/GameOverP2Background.png");
    loadTexture(this->idleHomepageButtonTexture, "gameOver/IdleHomepageButton.png");
    loadTexture(this->activeHomepageButtonTexture, "gameOver/ActiveHomepageButton.png");

    setSprite(sf::Vector2f(0, 0), sf::Vector2f(5, 5), this->gameOverWinBackgroundTexture, this->backgroundWinSprite);
    setSprite(sf::Vector2f(0, 0), sf::Vector2f(5, 5), this->gameOverLoseBackgroundTexture, this->backgroundLoseSprite);
    setSprite(sf::Vector2f(0, 0), sf::Vector2f(5, 5), this->gameOverP1BackgroundTexture, this->backgroundP1Sprite);
    setSprite(sf::Vector2f(0, 0), sf::Vector2f(5, 5), this->gameOverP2BackgroundTexture, this->backgroundP2Sprite);

    this->homepageButton = new Button(sf::Vector2f(136 * 5, 108 * 5), sf::Vector2f(5, 5), this->idleHomepageButtonTexture, this->activeHomepageButtonTexture);
}

GameOver::GameOver(const GameOver &source) {
    this->gameOverWinBackgroundTexture = source.gameOverWinBackgroundTexture;
    this->gameOverLoseBackgroundTexture = source.gameOverLoseBackgroundTexture;
    this->gameOverP1BackgroundTexture = source.gameOverP1BackgroundTexture;
    this->gameOverP2BackgroundTexture = source.gameOverP2BackgroundTexture;
    this->idleHomepageButtonTexture = source.idleHomepageButtonTexture;
    this->activeHomepageButtonTexture = source.activeHomepageButtonTexture;
    this->backgroundWinSprite = source.backgroundWinSprite;
    this->backgroundLoseSprite = source.backgroundLoseSprite;
    this->backgroundP1Sprite = source.backgroundP1Sprite;
    this->backgroundP2Sprite = source.backgroundP2Sprite;
    this->mousePosition = source.mousePosition;
    this->event = source.event;
    this->homepageButton = new Button(*(source.homepageButton));
}

GameOver::~GameOver() {
    delete this->homepageButton;
    this->homepageButton = nullptr;
}

screen::GameOver &GameOver::operator=(const GameOver &source) {
    if (this == &source) {
        return *this;
    } else {
        this->gameOverWinBackgroundTexture = source.gameOverWinBackgroundTexture;
        this->gameOverLoseBackgroundTexture = source.gameOverLoseBackgroundTexture;
        this->gameOverP1BackgroundTexture = source.gameOverP1BackgroundTexture;
        this->gameOverP2BackgroundTexture = source.gameOverP2BackgroundTexture;
        this->idleHomepageButtonTexture = source.idleHomepageButtonTexture;
        this->activeHomepageButtonTexture = source.activeHomepageButtonTexture;
        this->backgroundWinSprite = source.backgroundWinSprite;
        this->backgroundLoseSprite = source.backgroundLoseSprite;
        this->backgroundP1Sprite = source.backgroundP1Sprite;
        this->backgroundP2Sprite = source.backgroundP2Sprite;
        this->mousePosition = source.mousePosition;
        this->event = source.event;
        this->homepageButton = source.homepageButton;
        return *this;
    }
}

void GameOver::update(sf::RenderWindow &gui, sf::Vector2f mousePosition) {
    updateMousePosition(gui, mousePosition);
    this->homepageButton->updateButtonState(mousePosition);
}

void GameOver::poll(sf::RenderWindow &gui) {
    while (gui.pollEvent(this->event)) {
        switch (this->event.type) {

            case sf::Event::Closed:
                gui.close();
                break;

            case sf::Event::MouseButtonReleased:
                if ((event.mouseButton.button == sf::Mouse::Left) && (this->homepageButton->getButtonState())) {
                    State::changeScreen(Screens::HOMEPAGE);
                    break;
                } else {
                    break;
                }

            default:
                break;
        }
    }
}

void GameOver::render(sf::RenderWindow &gui) {
    gui.clear();
    if (State::gameMode == State::GameMode::SINGLE_PLAYER) {
        if (State::player == State::Player::P1) {
            gui.draw(this->backgroundLoseSprite);
        } else {
            gui.draw(this->backgroundWinSprite);
        }
    } else {
        if (State::player == State::Player::P1) {
            gui.draw(this->backgroundP2Sprite);
        } else {
            gui.draw(this->backgroundP1Sprite);
        }
    }

    homepageButton->render(gui);

    if (State::getCurrentScreen() == Screens::GAME_OVER) {
        gui.display();
    }
}

void GameOver::run(sf::RenderWindow &gui) {
    this->update(gui, this->mousePosition);
    this->poll(gui);
    this->render(gui);
}