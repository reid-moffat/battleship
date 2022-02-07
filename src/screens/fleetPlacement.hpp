/**
 * Front-end class that defines the behaviour of the Fleet Placement screens
 */

#ifndef BATTLESHIP_FLEETPLACEMENT_H
#define BATTLESHIP_FLEETPLACEMENT_H

#include "../controllers/screenTemplate.hpp"
#include "../entity/coordinate.hpp"

using entity::Coordinate;

namespace screen {
    class FleetPlacement : public ScreenTemplate {
    public:
        /**
         *
         */
        static FleetPlacement &getInstance();

        // Do not allow copying of this screen's instance
        FleetPlacement(const FleetPlacement &source) = delete;

        // Do not allow assignment of this screen's instance
        FleetPlacement &operator=(const FleetPlacement &source) = delete;

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
            BackgroundDefaultTexture,
            BackgroundP1Texture,
            BackgroundP2Texture,

            BattleshipTexture,
            AircraftCarrierTexture,
            DestroyerTexture,
            SubmarineTexture,
            PatrolBoatTexture,
            RowBoatTexture,

            IdleReadyButtonTexture,
            ActiveReadyButtonTexture,
            IdleRandomizeButtonTexture,
            ActiveRandomizeButtonTexture,
            IdleInstructionsButtonTexture,
            ReadyInstructionsButtonTexture
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

        // Ships on this screen, with their name, top left coordinate and if it is horizontal
        map<shipNames, tuple<Coordinate, bool>> ships;

        // If a ship orientation has been generated yet
        bool layoutGenerated;

        // Adds a coordinate to a vector if the x and y are valid
        static void addCoord(vector<Coordinate> &coordinates, int x, int y);

        // Generates a random fleet layout
        void randomize();

        // Updates ship sprites and orientations
        void updateFleetLayout();

        //Resets ship sprites and orientations
        void resetFleetLayout();
    };
}// namespace screen

#endif// BATTLESHIP_FLEETPLACEMENT_H