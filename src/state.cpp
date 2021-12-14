/**
 * Global game state implementation
 */

#include "../include/state.h"

using std::string;

bool State::lockedFlag = false;

const int State::width = 1920;
const int State::height = 1080;

State::Player State::player = State::Player::P1;
State::GameMode State::gameMode = State::GameMode::SinglePlayer;
State::Difficulty State::difficulty = State::Difficulty::EASY;

Screens State::previous = Screens::HOMEPAGE;
Screens State::current = Screens::HOMEPAGE;

void State::loadTexture(sf::Texture &texture, const std::string &path) {
    if (!texture.loadFromFile("../res/images/" + path)) {
        exit(-1);
    }
}

void State::setSprite(sf::Vector2f position, sf::Vector2f scale, const sf::Texture &spriteTexture, sf::Sprite &sprite) {
    sprite.setTexture(spriteTexture);
    sprite.setPosition(position);
    sprite.setScale(scale);
}

Screens State::getCurrentScreen() {
    return State::current;
}

Screens State::getPreviousScreen() {
    return State::previous;
}

void State::changeScreen(Screens newScreen) {
    if (State::current == newScreen) {
        throw std::invalid_argument("Error: You are trying to swap to the screen that is already being rendered");
    }

    State::previous = State::current;
    State::current = newScreen;
}

void State::previousScreen() {
    switch (State::current) {
        case Screens::HOMEPAGE:// Cannot go back from the homepage
            throw std::invalid_argument("Error: You can't go back from the home screen");
        case Screens::INSTRUCTIONS:// Goes back to the previously rendered screen for Instructions
            State::current = State::previous;
            break;
        case Screens::GAME_MODE_SELECTION:// Go back to the homepage for game mode selection
            State::current = Screens::HOMEPAGE;
            break;
        case Screens::DIFFICULTY_SELECTION:// Go back to game mode selection for difficulty selection
            State::current = Screens::GAME_MODE_SELECTION;
            break;
        default:
            std::map<Screens, std::string> screenNames = {{Screens::HOMEPAGE, "homepage"},
                                                          {Screens::FLEET_PLACEMENT, "homepage"},
                                                          {Screens::GAMEPLAY, "homepage"},
                                                          {Screens::INTERMEDIARY, "homepage"},
                                                          {Screens::GAME_OVER, "homepage"}};
            throw std::invalid_argument(string("Error: You can't go back from the current screen (") + screenNames[State::current] + "");
    }
}

void State::updateMousePosition(sf::RenderWindow &gui, sf::Vector2f &mousePosition) {
    mousePosition = gui.mapPixelToCoords(sf::Mouse::getPosition(gui));
}