/**
 * File: button.cpp
 * Description: Front-end class that creates buttons and manages button states, textures, and sprites
 */

#include "../../include/entity/button.h"

using entity::Button;

Button::Button(sf::Vector2f position, sf::Vector2f scale, sf::Texture idleTexture, sf::Texture activeTexture) {
    this->buttonState = false;
    this->idleTexture = idleTexture;
    this->activeTexture = activeTexture;
    this->sprite.setTexture(this->idleTexture);
    this->sprite.setPosition(position);
    this->sprite.setScale(scale);
}

Button::Button(const Button &source) {
    this->buttonState = source.buttonState;
    this->idleTexture = source.idleTexture;
    this->activeTexture = source.activeTexture;
    this->sprite = source.sprite;
}

Button::~Button() {
}

Button &Button::operator=(const Button &source) {
    if (this == &source) {
        return *this;
    } else {
        this->buttonState = source.buttonState;
        this->idleTexture = source.idleTexture;
        this->activeTexture = source.activeTexture;
        this->sprite = source.sprite;
        return *this;
    }
}

void Button::render(sf::RenderWindow &window) const {
    window.draw(this->sprite);
}

const bool Button::getButtonState() const {
    return this->buttonState;
}

void Button::updateButtonState(const sf::Vector2f mousePosition) {
    if (this->sprite.getGlobalBounds().contains(mousePosition)) {
        this->buttonState = true;
        this->sprite.setTexture(this->activeTexture);
    } else {
        this->buttonState = false;
        this->sprite.setTexture(this->idleTexture);
    }
}