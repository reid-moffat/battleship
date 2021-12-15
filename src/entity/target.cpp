/**
 * File: target.cpp
 * Description: Front-end class that creates and manages the target
 */

#include "../../include/entity/target.hpp"

using entity::Target;

Target::Target(Coordinate coordinate, sf::Vector2f position, sf::Vector2f scale, sf::Texture idleTexture, sf::Texture activeTexture) {
    this->targetState = false;
    this->targetCoordinate = coordinate;
    this->idleTexture = idleTexture;
    this->activeTexture = activeTexture;
    this->sprite.setTexture(this->idleTexture);
    this->sprite.setPosition(position);
    this->sprite.setScale(scale);
}

void Target::render(sf::RenderWindow &window) const {
    window.draw(this->sprite);
}

const bool Target::getTargetState() const {
    return this->targetState;
}

const Coordinate Target::getTargetCoordinate() const {
    return this->targetCoordinate;
}

void Target::updateTargetState(const sf::Vector2f mousePosition) {
    if (this->sprite.getGlobalBounds().contains(mousePosition)) {
        this->targetState = true;
        this->sprite.setTexture(this->activeTexture);
    } else {
        this->targetState = false;
        this->sprite.setTexture(this->idleTexture);
    }
}