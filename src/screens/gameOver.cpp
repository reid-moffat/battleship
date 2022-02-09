/**
 * Description: Front-end class that defines the behaviour of the Game Over screens
 */

#include "gameOver.hpp"

using screen::GameOver;

std::unique_ptr<GameOver> GameOver::instance = nullptr;

GameOver::GameOver() : ScreenTemplate() {
    // Data required for all the SFML objects on this screen
    const vector<string> texturePaths = {
            "GameOverWinBackground.png",
            "GameOverLoseBackground.png",
            "GameOverP1Background.png",
            "GameOverP2Background.png",

            "IdleHomepageButton.png",
            "ActiveHomepageButton.png",
    };
    const vector<sprite> sprites = {
            {sf::Vector2f(0, 0), sf::Vector2f(5, 5), WinBackgroundTexture},
            {sf::Vector2f(0, 0), sf::Vector2f(5, 5), LoseBackgroundTexture},
            {sf::Vector2f(0, 0), sf::Vector2f(5, 5), P1BackgroundTexture},
            {sf::Vector2f(0, 0), sf::Vector2f(5, 5), P2BackgroundTexture},
    };
    const vector<button> buttons = {
            {sf::Vector2f(136 * 5, 108 * 5), sf::Vector2f(5, 5),
             IdleHomepageButtonTexture, ActiveHomepageButtonTexture},
    };

    // Initialize SFML objects
    this->resources = ScreenResourceManager("gameOver", texturePaths, sprites, buttons);
}

GameOver &screen::GameOver::getInstance() {
    if (instance == nullptr) {
        instance.reset(new GameOver());
    }
    return *instance;
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
                    State::changeScreen(Screens::Homepage);
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

    if (State::gameMode == State::GameMode::SINGLE_PLAYER) {
        if (State::player == State::Player::P1) {
            gui.draw(resources.getSprite(spriteNames::BackgroundLose));
        } else {
            gui.draw(resources.getSprite(spriteNames::BackgroundWin));
        }
    } else {
        if (State::player == State::Player::P1) {
            gui.draw(resources.getSprite(spriteNames::BackgroundP2));
        } else {
            gui.draw(resources.getSprite(spriteNames::BackgroundP1));
        }
    }

    resources.getButton(buttonNames::Homepage).render(gui);

    gui.display();
}
