/**
 * Front-end class that defines the behaviour of the Fleet Placement screens
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

    private:
        // Singleton instance
        static std::unique_ptr<FleetPlacement> instance;

        // Singleton constructor
        FleetPlacement();

        // SFML event loop helpers
        void update() override;
        void poll() override;
        void render() override;

        // Names to refer to resources on this screen
        enum textureNames {
            BackgroundDefault_,
            BackgroundP1_,
            BackgroundP2_,
            IdleReadyButton,
            ActiveReadyButton,
            IdleRandomizeButton,
            ActiveRandomizeButton,
            IdleInstructionsButton,
            ReadyInstructionsButton,
            Battleship_,
            AircraftCarrier_,
            Destroyer_,
            Submarine_,
            PatrolBoat_,
            RowBoat_
        };
        enum spriteNames {
            BackgroundDefault,
            BackgroundP1,
            BackgroundP2,
            Battleship,
            AircraftCarrier,
            Destroyer,
            Submarine,
            PatrolBoat,
            RowBoat
        };
        enum buttonNames {
            Ready,
            Randomize,
            Instructions
        };

        /**
         *
         */
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

    };
}// namespace screen

#endif// BATTLESHIP_FLEETPLACEMENT_H