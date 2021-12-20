/**
 * Target class implementation
 */

#include "target.hpp"
#include "helpers.hpp"

using entity::Target;

sf::Texture Target::idleTexture = *new sf::Texture();
sf::Texture Target::activeTexture = *new sf::Texture();

void entity::Target::initializeTextures() {
    loadTexture(Target::idleTexture, "gameplay/idlePrimaryTarget.png");
    loadTexture(Target::activeTexture, "gameplay/ActivePrimaryTarget.png");
}

Target::Target(Coordinate coordinate, sf::Vector2f position, sf::Vector2f scale) {
    this->targetState = false;
    this->targetCoordinate = coordinate;
    this->sprite.setTexture(idleTexture);
    this->sprite.setPosition(position);
    this->sprite.setScale(scale);
}

void Target::render(sf::RenderWindow &window) const {
    window.draw(this->sprite);
}

bool Target::getTargetState() const {
    return this->targetState;
}

Coordinate Target::getTargetCoordinate() const {
    return this->targetCoordinate;
}

void Target::updateTargetState(const sf::Vector2f mousePosition) {
    if (this->sprite.getGlobalBounds().contains(mousePosition)) {
        this->targetState = true;
        this->sprite.setTexture(activeTexture);
    } else {
        this->targetState = false;
        this->sprite.setTexture(idleTexture);
    }
}
