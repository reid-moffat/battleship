/**
 * Global game state implementation
 */

#include "state.hpp"

using std::string;

// Initialize the game state variables with their starting values
unique_ptr<sf::RenderWindow> State::gui = nullptr;
sf::Event State::event;
bool State::lockedFlag = false;

State::Player State::player = State::Player::P1;
State::GameMode State::gameMode = State::GameMode::SINGLE_PLAYER;
State::Difficulty State::difficulty = State::Difficulty::EASY;

Screens State::previous = Screens::HOMEPAGE;
Screens State::current = Screens::HOMEPAGE;

Screens State::getCurrentScreen() {
    return State::current;
}

Screens State::getPreviousScreen() {
    return State::previous;
}

void State::changeScreen(Screens newScreen) {
    if (State::current == newScreen) {
        throw std::invalid_argument("Error: You are trying to swap to the screens that is already being rendered");
    }

    State::previous = State::current;
    State::current = newScreen;
}

void State::previousScreen() {
    switch (State::current) {
        case Screens::HOMEPAGE:// Cannot go back from the homepage
            throw std::invalid_argument("Error: You can't go back from the home screen");
        case Screens::INSTRUCTIONS:// Goes back to the previously rendered screens for Instructions
            State::current = State::previous;
            break;
        case Screens::GAME_MODE_SELECTION:// Go back to the homepage for game mode selection
            State::current = Screens::HOMEPAGE;
            break;
        case Screens::DIFFICULTY_SELECTION:// Go back to game mode selection for difficulty selection
            State::current = Screens::GAME_MODE_SELECTION;
            break;
        default:
            // TODO: Update this
            std::map<Screens, std::string> screenNames = {{Screens::HOMEPAGE, "homepage"},
                                                          {Screens::FLEET_PLACEMENT, "homepage"},
                                                          {Screens::GAMEPLAY, "Gameplay"},
                                                          {Screens::INTERMEDIARY, "Intermediary"},
                                                          {Screens::GAME_OVER, "Game Over"}};
            throw std::invalid_argument(string("Error: You can't go back from the current screens (") + screenNames[State::current] + "");
    }
}

sf::Vector2f State::getMousePosition() {
    return State::gui->mapPixelToCoords(sf::Mouse::getPosition(*State::gui));
}
