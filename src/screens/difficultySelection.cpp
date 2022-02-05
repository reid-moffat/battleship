/**
 * Front-end class that defines the behaviour of the Difficulty selection screens
 */

#include "difficultySelection.hpp"

using screen::DifficultySelection;

std::unique_ptr<DifficultySelection> DifficultySelection::instance = nullptr;

DifficultySelection::DifficultySelection() : ScreenTemplate() {
    const vector<string> texturePaths{"difficultySelection/DifficultyBackground.png",
                                      "difficultySelection/IdleEasyButton.png", "difficultySelection/ActiveEasyButton.png",
                                      "difficultySelection/IdleHardButton.png", "difficultySelection/ActiveHardButton.png",
                                      "difficultySelection/IdleBackButton.png", "difficultySelection/ActiveBackButton.png",
                                      "difficultySelection/IdleInstructionsButton.png", "difficultySelection/ActiveInstructionsButton.png"};
    const vector<sprite> sprites = {{sf::Vector2f(0, 0), sf::Vector2f(5, 5), textureNames::Background_}};
    const vector<button> buttons = {{sf::Vector2f(88 * 5, 92 * 5), sf::Vector2f(5, 5), textureNames::IdleEasyButton, textureNames::ActiveEasyButton},
                                    //{sf::Vector2f(200 * 5, 92 * 5), sf::Vector2f(5, 5), textureNames::IdleHardButton, textureNames::ActiveHardButton},
                                    //{sf::Vector2f(320 * 5, 12 * 5), sf::Vector2f(5, 5), textureNames::IdleBackButton, textureNames::ActiveBackButton},
                                    {sf::Vector2f(352 * 5, 12 * 5), sf::Vector2f(5, 5), textureNames::IdleInstructionsButton, textureNames::ActiveInstructionsButton}};
    this->resources = ScreenResourceManager(texturePaths, sprites, buttons);


    // TODO: Remove these manual textures and buttons
    loadTexture(this->idleEasyButtonTexture, "difficultySelection/IdleEasyButton.png");
    loadTexture(this->activeEasyButtonTexture, "difficultySelection/ActiveEasyButton.png");
    loadTexture(this->idleHardButtonTexture, "difficultySelection/IdleHardButton.png");
    loadTexture(this->activeHardButtonTexture, "difficultySelection/ActiveHardButton.png");
    loadTexture(this->idleBackButtonTexture, "difficultySelection/IdleBackButton.png");
    loadTexture(this->activeBackButtonTexture, "difficultySelection/ActiveBackButton.png");
    loadTexture(this->idleInstructionsButton, "difficultySelection/IdleInstructionsButton.png");
    loadTexture(this->activeInstructionsButton, "difficultySelection/ActiveInstructionsButton.png");

    this->easyButton = std::make_unique<Button>(sf::Vector2f(88 * 5, 92 * 5), sf::Vector2f(5, 5), this->idleEasyButtonTexture, this->activeEasyButtonTexture);
    this->hardButton = std::make_unique<Button>(sf::Vector2f(200 * 5, 92 * 5), sf::Vector2f(5, 5), this->idleHardButtonTexture, this->activeHardButtonTexture);
    this->backButton = std::make_unique<Button>(sf::Vector2f(320 * 5, 12 * 5), sf::Vector2f(5, 5), this->idleBackButtonTexture, this->activeBackButtonTexture);
    this->instructionsButton = std::make_unique<Button>(sf::Vector2f(352 * 5, 12 * 5), sf::Vector2f(5, 5), this->idleInstructionsButton, this->activeInstructionsButton);
}

DifficultySelection &screen::DifficultySelection::getInstance() {
    if (instance == nullptr) {
        instance.reset(new DifficultySelection());
    }
    return *instance;
}

void DifficultySelection::update() {
    sf::Vector2f mousePosition = State::getMousePosition();
    resources.getButton(buttonNames::EasyButton).updateButtonState(mousePosition);
    this->easyButton->updateButtonState(mousePosition);
    this->hardButton->updateButtonState(mousePosition);
    this->backButton->updateButtonState(mousePosition);
    this->instructionsButton->updateButtonState(mousePosition);
}

void DifficultySelection::poll() {
    sf::RenderWindow &gui = *State::gui;
    sf::Event &event = State::event;

    while (gui.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                gui.close();
                break;
            case sf::Event::MouseButtonReleased:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (resources.getButton(EasyButton).getButtonState()) {
                        State::difficulty = State::Difficulty::EASY;
                        State::changeScreen(Screens::FLEET_PLACEMENT);
                        break;
                    } else if (this->hardButton->getButtonState()) {
                        State::difficulty = State::Difficulty::HARD;
                        State::changeScreen(Screens::FLEET_PLACEMENT);
                        break;
                    } else if (this->backButton->getButtonState()) {
                        State::changeScreen(Screens::GAME_MODE_SELECTION);
                        break;
                    } else if (this->instructionsButton->getButtonState()) {
                        State::changeScreen(Screens::INSTRUCTIONS);
                        break;
                    } else {
                        break;
                    }
                }
            default:
                break;
        }
    }
}

void DifficultySelection::render() {
    sf::RenderWindow &gui = *State::gui;
    gui.clear();

    gui.draw(resources.getSprite(spriteNames::Background));
    resources.getButton(EasyButton).render(gui);
    // resources.getButton(buttonNames::HardButton).render(gui);
    // resources.getButton(buttonNames::InstructionsButton).render(gui);
    // resources.getButton(buttonNames::BackButton).render(gui);
    //  easyButton->render(gui);
    hardButton->render(gui);
    backButton->render(gui);
    instructionsButton->render(gui);

    if (State::getCurrentScreen() == Screens::DIFFICULTY_SELECTION) {
        gui.display();
    }
}
