/**
 * Front-end class that defines the behaviour of the Gameplay screens
 */

#ifndef BATTLESHIP_GAMEPLAY_H
#define BATTLESHIP_GAMEPLAY_H

#include "../controllers/screenTemplate.hpp"
#include "../entity/grid.hpp"
#include "../entity/target.hpp"
#include <set>

using entity::Grid;
using entity::SquareType;
using entity::Target;
using std::set;

//Orientation of ships: Its name, top left coordinate and if it's horizontal
typedef map<shipNames, tuple<Coordinate, bool>> shipOrientations;

namespace screen {
    class Gameplay : public ScreenTemplate {
    public:
        /**
         * Returns the instance of this screen
         */
        static Gameplay &getInstance();

        /**
         * Initializes P1's grid
         */
        void setP1Grid(const shipOrientations &ships);

        /**
         * Initializes P2's grid
         */
        void setP2Grid(const shipOrientations &ships);

        // Do not allow copying of this screen's instance
        Gameplay(const Gameplay &source) = delete;

        // Do not allow assignment of this screen's instance
        Gameplay &operator=(const Gameplay &source) = delete;

    private:
        // Singleton instance
        static std::unique_ptr<Gameplay> instance;

        // Singleton constructor
        Gameplay();

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

            BattleshipSunkTexture,
            AircraftCarrierSunkTexture,
            DestroyerSunkTexture,
            SubmarineSunkTexture,
            PatrolBoatSunkTexture,
            RowBoatSunkTexture,

            PrimaryHitMarkerTexture,
            PrimaryMissMarkerTexture,
            SecondaryHitMarkerTexture,
            SecondaryMissMarkerTexture,
            SecondaryTargetTexture,

            IdleSurrenderButtonTexture,
            ActiveSurrenderButtonTexture,
            IdleInstructionsButtonTexture,
            ActiveInstructionsButtonTexture
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
            RowBoat,

            BattleShipSunk,
            AircraftCarrierSunk,
            DestroyerSunk,
            SubmarineSunk,
            PatrolBoatSunk,
            RowBoatSunk,

            PrimaryHitMarker,
            PrimaryMissMarker,
            SecondaryHitMarker,
            SecondaryMissMarker,
            SecondaryTarget
        };
        enum buttonNames {
            Surrender,
            Instructions
        };


        // Player's grids (state of each square) and fleet layouts (where their ships are located)
        std::unique_ptr<shipOrientations> fleetLayoutP1;
        std::unique_ptr<shipOrientations> fleetLayoutP2;
        std::unique_ptr<Grid> gridP1;
        std::unique_ptr<Grid> gridP2;

        // All the targets for this screen
        vector<Target> targetVector;

        // Markers for each player that show the status of the other player's board (hits, current target)
        vector<sf::Sprite> primaryMarkersP1Vector;
        vector<sf::Sprite> primaryMarkersP2Vector;
        vector<sf::Sprite> secondaryMarkersP1Vector;
        vector<sf::Sprite> secondaryMarkersP2Vector;

        // Possible coordinates that the environment can attack
        set<Coordinate> coordinateSet;

        // Selects (and removes) a random coordinate from the coordinates that have not been attacked yet
        Coordinate randomAttack();

        // Checks if all the ships on a grid have been sunk
        inline static bool lost(Grid &grid);

        // Updates all the markers on the grid for a given attack on a given coordinate
        void updateGridMarkers(SquareType attack, Coordinate coordinate);

        // Resets all markers for both grids (use when the game is over)
        void resetGridMarkers();

        // Updates the temporary target marker over the user's cursor
        inline void updateSecondaryTarget(Coordinate coordinate);

        // Registers an attack, updating the required grid
        void attack(Coordinate &attack);

        // Updates the location of each ship sprite with a given fleet layout
        void setFleetLayout(shipOrientations &fleetLayout);

        // Draws any sunken ships of a specific grid to the screen
        void renderSunkShips(Grid &grid);

        // How many milliseconds the program execution should pause for after an attack
        static constexpr int sleepTimeMS = 400;

        // Sleeps the process for Gameplay::sleepTimeMS milliseconds works for (windows and Unix-based systems)
        inline static void sleepMS();

    };
}// namespace screen

#endif// BATTLESHIP_GAMEPLAY_H