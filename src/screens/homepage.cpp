/**
 * Description: Front-end class that defines the behaviour of the Homepage screens
 */

#include "homepage.hpp"

using screen::Homepage;

std::unique_ptr<Homepage> Homepage::instance = nullptr;

Homepage::Homepage() {
    const vector<string> texturePaths{
            "HomepageBackground.png",
            "IdlePlayButton.png",
            "ActivePlayButton.png",
    };
    const vector<sprite> sprites = {
            {sf::Vector2f(0, 0), sf::Vector2f(5, 5), BackgroundTexture},
    };
    const vector<button> buttons = {
            {sf::Vector2f(232 * 5, 64 * 5), sf::Vector2f(5, 5),
             IdlePlayButtonTexture, ActivePlayButtonTexture},
    };

    // Initialize SFML objects
    this->resources = ScreenResourceManager("homepage", texturePaths, sprites, buttons);
}

Homepage &Homepage::getInstance() {
    if (instance == nullptr) {
        instance.reset(new Homepage());
    }
    return *instance;
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
                if (event.mouseButton.button == sf::Mouse::Left && resources.getButton(buttonNames::PlayButton).getButtonState()) {
                    State::changeScreen(Screens::GameModeSelection);
                }
                break;
            default:
                break;
        }
    }
}

void Homepage::render() {
    sf::RenderWindow &gui = *State::gui;
    gui.clear();

    gui.draw(resources.getSprite(spriteNames::Background));
    resources.getButton(buttonNames::PlayButton).render(gui);

    gui.display();
}
