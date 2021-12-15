/**
 * File: fleetPlacement.h
 * Description: Front-end class that defines the behaviour of the Fleet Placement screen
 */

#ifndef BATTLESHIP_FLEETPLACEMENT_H
#define BATTLESHIP_FLEETPLACEMENT_H

#include "../entity/button.hpp"
#include "../entity/coordinate.hpp"
#include "../entity/shipNames.hpp"
#include "screenTemplate.hpp"

#include <SFML/System.hpp>

#include <random>
#include <vector>

using entity::Button;
using entity::Coordinate;
using entity::shipSizes;
using entity::shipsNames;
using std::map;
using std::tuple;
using std::vector;

namespace screen {
    class FleetPlacement : public ScreenTemplate {
    private:
        /**
         * Default background texture
         */
        sf::Texture fleetPlacementDefaultBackgroundTexture;

        /**
         * P1 background texture
         */
        sf::Texture fleetPlacementP1BackgroundTexture;

        /**
         * P2 background texture
         */
        sf::Texture fleetPlacementP2BackgroundTexture;

        /**
         * Idle ready button texture
         */
        sf::Texture idleReadyButtonTexture;

        /**
         * Active ready button texture
         */
        sf::Texture activeReadyButtonTexture;

        /**
         * Idle randomize button texture
         */
        sf::Texture idleRandomizeButtonTexture;

        /**
         * Active randomize button texture
         */
        sf::Texture activeRandomizeButtonTexture;

        /**
         * Idle instructions button texture
         */
        sf::Texture idleInstructionsButtonTexture;

        /**
         * Active instructions button texture
         */
        sf::Texture activeInstructionsButtonTexture;

        /**
         * Battleship texture
         */
        sf::Texture battleshipTexture;

        /**
         * Aircraft carrier texture
         */
        sf::Texture aircraftCarrierTexture;

        /**
         * Destroyer texture
         */
        sf::Texture destroyerTexture;

        /**
         * Submarine texture
         */
        sf::Texture submarineTexture;

        /**
         * Patrol boat texture
         */
        sf::Texture patrolBoatTexture;

        /**
         * Row boat texture
         */
        sf::Texture rowBoatTexture;

        /**
         * Background default sprite
         */
        sf::Sprite backgroundDefaultSprite;

        /**
         * Background P1 sprite
         */
        sf::Sprite backgroundP1Sprite;

        /**
         * Background P2 sprite
         */
        sf::Sprite backgroundP2Sprite;

        /**
         * Battleship sprite
         */
        sf::Sprite battleshipSprite;

        /**
         * Aircraft carrier sprite
         */
        sf::Sprite aircraftCarrierSprite;

        /**
         * Destroyer sprite
         */
        sf::Sprite destroyerSprite;

        /**
         * Submarine sprite
         */
        sf::Sprite submarineSprite;

        /**
         * Patrol Boat sprite
         */
        sf::Sprite patrolBoatSprite;

        /**
         * Row boat sprite
         */
        sf::Sprite rowBoatSprite;

        /**
         * Ready button
         */
        Button *readyButton;

        /**
         * Randomize button
         */
        Button *randomizeButton;

        /**
         * Instructions button
         */
        Button *instructionsButton;

        /**
         * Mouse position vector
         */
        sf::Vector2f mousePosition;

        /**
         * System event
         */
        sf::Event event{};

        bool layoutGenerated;

        /**
         * Ships map:
         * ShipNames -> specifies the ship name and size
         * Coordinate -> specifies the topmost or leftmost coordinate of the ship
         * Bool -> specifies the ship orientation (horizontal = true)
         */
        map<shipsNames, tuple<Coordinate, bool>> ships;

        /**
         * Adds a coordinate to a vector if the coordinate is valid
         */
        static void addCoord(vector<Coordinate> &coordinates, int x, int y);

        /**
         * Generates a random fleet layout
         */
        void randomize();

        /**
         * Updates ship sprites and orientations
         */
        void updateFleetLayout();

        /**
         * Resets ship sprites and orientations
         */
        void resetFleetLayout();

        /**
         * Calls helpers::updateMousePosition() and entity::Button::updateButtonState()
         */
        void update(sf::RenderWindow &gui, sf::Vector2f mousePos);

        /**
         * Polls for system events
         */
        void poll(sf::RenderWindow &gui);

        /**
         * Renders all sprites
         */
        void render(sf::RenderWindow &gui);

    public:
        /**
         * Constructor
         */
        FleetPlacement();

        /**
         * Copy constructor
         */
        FleetPlacement(const FleetPlacement &source);

        /**
         * Destructor
         */
        ~FleetPlacement() override;

        /**
         * Overloaded assignment operator
         */
        FleetPlacement &operator=(const FleetPlacement &source);

        /**
         * Overridden run method of screenTemplate
         */
        void run(sf::RenderWindow &gui) override;
    };
}// namespace screen

#endif// BATTLESHIP_FLEETPLACEMENT_H