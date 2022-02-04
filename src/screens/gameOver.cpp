/**
 * Description: Front-end class that defines the behaviour of the Game Over screens
 */

#include "gameOver.hpp"

using screen::GameOver;

std::unique_ptr<GameOver> GameOver::instance = nullptr;

GameOver::GameOver() : ScreenTemplate() {
    const vector<string> texturePaths = {"gameOver/GameOverWinBackground.png", "gameOver/GameOverLoseBackground.png",
                                         "gameOver/GameOverP1Background.png", "gameOver/GameOverP2Background.png",
                                         "gameOver/IdleHomepageButton.png", "gameOver/ActiveHomepageButton.png"};
    const vector<sprite> sprites = {{sf::Vector2f(0, 0), sf::Vector2f(5, 5), textureNames::GameOverWinBackground},
                                    {sf::Vector2f(0, 0), sf::Vector2f(5, 5), textureNames::GameOverLoseBackground},
                                    {sf::Vector2f(0, 0), sf::Vector2f(5, 5), textureNames::GameOverP1Background},
                                    {sf::Vector2f(0, 0), sf::Vector2f(5, 5), textureNames::GameOverP2Background}};
    const vector<button> buttons = {{sf::Vector2f(136 * 5, 108 * 5), sf::Vector2f(5, 5),
                                     textureNames::IdleHomepageButton, textureNames::ActiveHomepageButton}};
    this->resources = ScreenResourceManager(texturePaths, sprites, buttons);

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

void GameOver::update() {
    sf::Vector2f mousePosition = State::getMousePosition();
    this->homepageButton->updateButtonState(mousePosition);
}

void GameOver::poll() {
    sf::RenderWindow &gui = *State::gui;
    sf::Event &event = State::event;

    while (gui.pollEvent(event)) {
        switch (event.type) {

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

void GameOver::render() {
    sf::RenderWindow &gui = *State::gui;

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

GameOver &screen::GameOver::getInstance() {
    if (instance == nullptr) {
        instance.reset(new GameOver());
    }
    return *instance;
}
