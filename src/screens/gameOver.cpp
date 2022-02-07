/**
 * Description: Front-end class that defines the behaviour of the Game Over screens
 */

#include "gameOver.hpp"

using screen::GameOver;

std::unique_ptr<GameOver> GameOver::instance = nullptr;

GameOver &screen::GameOver::getInstance() {
    if (instance == nullptr) {
        instance.reset(new GameOver());
    }
    return *instance;
}

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
}

void GameOver::update() {
    sf::Vector2f mousePosition = State::getMousePosition();
    resources.getButton(buttonNames::Homepage).updateButtonState(mousePosition);
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
                if (event.mouseButton.button == sf::Mouse::Left && resources.getButton(buttonNames::Homepage).getButtonState()) {
                    State::changeScreen(Screens::HOMEPAGE);
                }
                break;
            default:
                break;
        }
    }
}

void GameOver::render() {
    sf::RenderWindow &gui = *State::gui;

    gui.clear();
    sf::Sprite background;
    if (State::gameMode == State::GameMode::SINGLE_PLAYER) {
        background = State::player == State::Player::P1 ? resources.getSprite(spriteNames::BackgroundLose) : resources.getSprite(spriteNames::BackgroundWin);
    } else {
        background = State::player == State::Player::P1 ? resources.getSprite(spriteNames::BackgroundP2) : resources.getSprite(spriteNames::BackgroundP1);
    }
    gui.draw(background);

    resources.getButton(buttonNames::Homepage).render(gui);

    if (State::getCurrentScreen() == Screens::GAME_OVER) {
        gui.display();
    }
}
