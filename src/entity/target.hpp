/**
 * Front-end class that creates and manages targets: a red box on squares the user is hovering over
 */

#ifndef BATTLESHIP_TARGET_H
#define BATTLESHIP_TARGET_H

#include "../entity/coordinate.hpp"
#include <SFML/Graphics.hpp>

using entity::Coordinate;
using std::string;

namespace entity {

    class Target {
    public:
        /**
         * Constructs a target on a coordinate
         */
        Target(Coordinate coordinate, sf::Vector2f position, sf::Vector2f scale);

        /**
         * Loads the static textures for the target
         */
        static void initializeTextures(const string& idlePath, const string& activePath);

        /**
         * Returns true if the target is active (i.e. the cursor is over the targetCoordinate)
         */
        bool getTargetState() const;

        /**
         * Returns the target coordinate
         */
        Coordinate getTargetCoordinate() const;

        /**
         * Renders the target sprite on the window
         */
        void render(sf::RenderWindow &window) const;

        /**
         * Updates the target state
         */
        void updateTargetState(sf::Vector2f mousePosition);

    private:
        // Idle target texture (same for all targets)
        static std::unique_ptr<sf::Texture> idleTexture;

        // Active target texture (same for all targets)
        static std::unique_ptr<sf::Texture> activeTexture;

        // Target's current sprite (idle or active)
        sf::Sprite sprite;

        // Target state
        bool isActive;

        // Location of the target
        Coordinate targetCoordinate;
    };

}// namespace entity

#endif// BATTLESHIP_TARGET_H