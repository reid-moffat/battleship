/**
 * File: fleetPlacement.h
 * Description: Front-end class that defines the behaviour of the Fleet Placement screens
 */

#ifndef BATTLESHIP_FLEETPLACEMENT_H
#define BATTLESHIP_FLEETPLACEMENT_H

#include "../controllers/screenTemplate.hpp"
#include "../entity/button.hpp"
#include "../entity/coordinate.hpp"
#include "../enums/shipNames.hpp"
#include <SFML/System.hpp>
#include <random>
#include <vector>

using entity::Button;
using entity::Coordinate;
using entity::shipNames;
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

        bool layoutGenerated;

        /**
         * Ships map:
         * ShipNames -> specifies the ship name and size
         * Coordinate -> specifies the topmost or leftmost coordinate of the ship
         * Bool -> specifies the ship orientation (horizontal = true)
         */
        map<shipNames, tuple<Coordinate, bool>> ships;

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
        void update();

        /**
         * Polls for system events
         */
        void poll();

        /**
         * Renders all sprites
         */
        void render();

        /**
         * Constructor
         */
        FleetPlacement();

        /**
         *
         */
        static FleetPlacement *instance;

    public:
        /**
         * Copy constructor
         */
        FleetPlacement(const FleetPlacement &source) = delete;

        /**
         * Overloaded assignment operator
         */
        FleetPlacement &operator=(const FleetPlacement &source) = delete;

        /**
         *
         */
        static FleetPlacement &getInstance();
    };
}// namespace screen

#endif// BATTLESHIP_FLEETPLACEMENT_H