/**
 * Target class implementation
 */

#include "target.hpp"
#include "../helpers/helperFunctions.hpp"
#include <memory>

using entity::Target;

std::unique_ptr<sf::Texture> Target::idleTexture = std::unique_ptr<sf::Texture>();
std::unique_ptr<sf::Texture> Target::activeTexture = std::unique_ptr<sf::Texture>();

void entity::Target::initializeTextures(const string &idlePath, const string &activePath) {
    Target::idleTexture = std::make_unique<sf::Texture>();
    Target::activeTexture = std::make_unique<sf::Texture>();

    loadTexture(*Target::idleTexture, "gameplay/" + idlePath);
    loadTexture(*Target::activeTexture, "gameplay/" + activePath);
}

Target::Target(Coordinate coordinate, sf::Vector2f position, sf::Vector2f scale) {
    this->isActive = false;
    this->targetCoordinate = coordinate;
    this->sprite.setTexture(*idleTexture);
    this->sprite.setPosition(position);
    this->sprite.setScale(scale);
}

void Target::render(sf::RenderWindow &window) const {
    window.draw(this->sprite);
}

bool Target::getTargetState() const {
    return this->isActive;
}

Coordinate Target::getTargetCoordinate() const {
    return this->targetCoordinate;
}

void Target::updateTargetState(const sf::Vector2f mousePosition) {
    if (this->sprite.getGlobalBounds().contains(mousePosition)) {
        this->isActive = true;
        this->sprite.setTexture(*activeTexture);
    } else {
        this->isActive = false;
        this->sprite.setTexture(*idleTexture);
    }
}
