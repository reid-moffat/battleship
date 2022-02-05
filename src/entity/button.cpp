/**
 * Front-end class that creates buttons and manages button states, textures, and sprites
 */

#include "button.hpp"
#include <memory>

using entity::Button;

Button::Button(const sf::Vector2f position, const sf::Vector2f scale, sf::Texture &idleTexture, sf::Texture &activeTexture) {
    this->active = false;
    this->idleTexture.reset(&idleTexture);
    this->activeTexture.reset(&activeTexture);

    this->sprite = std::make_unique<sf::Sprite>(*this->idleTexture);
    this->sprite->setPosition(position);
    this->sprite->setScale(scale);
}

bool Button::getButtonState() const {
    return this->active;
}

void Button::render(sf::RenderWindow &window) const {
    window.draw(*this->sprite);
}

void Button::updateButtonState(const sf::Vector2f mousePosition) {
    if (this->sprite->getGlobalBounds().contains(mousePosition)) {// Mouse is on the button
        this->active = true;
        this->sprite->setTexture(*this->activeTexture);
    } else {
        this->active = false;
        this->sprite->setTexture(*this->idleTexture);
    }
}
