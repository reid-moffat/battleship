/**
 * File: target.h
 * Description: Front-end class that creates and manages the target
 */

#ifndef BATTLESHIP_TARGET_H
#define BATTLESHIP_TARGET_H

#include "coordinate.hpp"

#include <SFML/Graphics.hpp>

using entity::Coordinate;

namespace entity {

    class Target {
    private:
        /**
         * Idle target exture
         */
        sf::Texture idleTexture;

        /**
         * Active target texture
         */
        sf::Texture activeTexture;

        /**
         * Target sprite
         */
        sf::Sprite sprite;

        /**
         * Target state (active = true and idle = false)
         */
        bool targetState;

        /**
         * Location of the target
         */
        Coordinate targetCoordinate;

    public:
        /**
         * Constructor
         */
        Target(Coordinate coordinate, sf::Vector2f position, sf::Vector2f scale, sf::Texture idleTexture, sf::Texture activeTexture);

        /**
         * Returns true if the target is active (i.e., the cursor is over the targetCoordinate)
         */
        const bool getTargetState() const;

        /**
         * Returns the target coordinate
         */
        const Coordinate getTargetCoordinate() const;

        /**
         * Renders the target sprite on the window
         */
        void render(sf::RenderWindow &window) const;

        /**
         * Updates the target state
         */
        void updateTargetState(const sf::Vector2f mousePosition);
    };

}// namespace entity

#endif// BATTLESHIP_TARGET_H