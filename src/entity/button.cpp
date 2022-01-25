/**
 * File: button.cpp
 * Description: Front-end class that creates buttons and manages button states, textures, and sprites
 */

#include "button.hpp"

using entity::Button;

Button::Button(sf::Vector2f position, sf::Vector2f scale, sf::Texture &idleTexture, sf::Texture &activeTexture) {
    this->active = false;
    this->idleTexture = &idleTexture;
    this->activeTexture = &activeTexture;

    this->sprite = new sf::Sprite(*this->idleTexture);
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

Button::Button(const Button &source) {
    this->active = source.active;
    this->idleTexture = source.idleTexture;
    this->activeTexture = source.activeTexture;
    this->sprite = source.sprite;
}

Button::~Button() {
    delete idleTexture;
    delete activeTexture;
    delete sprite;
}

Button &Button::operator=(const Button &source) {
    if (this == &source) {
        return *this;
    } else {
        this->active = source.active;
        this->idleTexture = source.idleTexture;
        this->activeTexture = source.activeTexture;
        this->sprite = source.sprite;
        return *this;
    }
}
