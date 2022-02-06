/**
 * Front-end class that defines the behaviour of the Gameplay screens
 */

#ifndef BATTLESHIP_GAMEPLAY_H
#define BATTLESHIP_GAMEPLAY_H

#include "../controllers/screenTemplate.hpp"
#include "../entity/button.hpp"
#include "../entity/coordinate.hpp"
#include "../entity/grid.hpp"
#include "../entity/target.hpp"
#include "../enums/shipNames.hpp"
#include <SFML/System.hpp>
#include <set>

using entity::Button;
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
         *
         */
        static Gameplay &getInstance();

        /**
         * Copy constructor
         */
        Gameplay(const Gameplay &source) = delete;

        /**
         * Overloaded assignment operator
         */
        Gameplay &operator=(const Gameplay &source) = delete;

        /**
         * Initializes P1 grid
         */
        void setP1Grid(const shipOrientations &ships);

        /**
         * Initializes P2 grid
         */
        void setP2Grid(const shipOrientations &ships);

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
         * Map of P1 fleet layout
         */
        std::unique_ptr<shipOrientations> fleetLayoutP1;

        /**
         * Map of P2 fleet layout
         */
        std::unique_ptr<shipOrientations> fleetLayoutP2;

        /**
         * P1 Grid
         */
        std::unique_ptr<Grid> gridP1;

        /**
         * P2 Grid
         */
        std::unique_ptr<Grid> gridP2;

        /**
         * Set of grid coordinates used by environment
         */
        set<Coordinate> coordinateSet;

        /**
         * Generates a set of grid coordinates
         */
        void createCoordinateSet();

        /**
         * Selects a random coordinate from screens::Gameplay::coordinateSet
         */
        Coordinate randomAttack();

        /**
         * Initializes target vector
         */
        void setTargetVector();

        /**
         * Checks if the game is lost for a specified player (true: P1, false: P2)
         */
        bool lost(Grid &grid);

        /**
         * Updates grid markers
         */
        void updateGridMarkers(SquareType attack, Coordinate coordinate);

        /**
         * Resets grid markers
         */
        void resetGridMarkers();

        /**
         * Updates secondary target
         */
        void updateSecondaryTarget(Coordinate coordinate);

        /**
         * Sleeps the process (works for windows and unix-based systems)
         */
        void sleepMS();

        /**
         * Updates grid state
         */
        void updateGrid(Coordinate &coordinate, sf::RenderWindow &grid);

        /**
         * Sets the fleet layout of the current player
         */
        void setFleetLayout(shipOrientations &fleetLayout);

        /**
         * Renders ship status
         */
        void renderShipStatus(Grid &grid);

        /**
         * The sleep time after a player attacks in milliseconds
         */
        static constexpr int sleepTimeMS = 400;


        sf::Texture gameplayDefaultBackgroundTexture;
        sf::Texture gameplayP1BackgroundTexture;
        sf::Texture gameplayP2BackgroundTexture;
        sf::Texture idleSurrenderButtonTexture;
        sf::Texture activeSurrenderButtonTexture;
        sf::Texture idleInstructionsButtonTexture;
        sf::Texture activeInstructionsButtonTexture;
        sf::Texture battleshipTexture;
        sf::Texture aircraftCarrierTexture;
        sf::Texture destroyerTexture;
        sf::Texture submarineTexture;
        sf::Texture patrolBoatTexture;
        sf::Texture rowBoatTexture;
        sf::Texture battleshipSunkTexture;
        sf::Texture aircraftCarrierSunkTexture;
        sf::Texture destroyerSunkTexture;
        sf::Texture submarineSunkTexture;
        sf::Texture patrolBoatSunkTexture;
        sf::Texture rowBoatSunkTexture;
        sf::Texture primaryHitMarkerTexture;
        sf::Texture primaryMissMarkerTexture;
        sf::Texture secondaryHitMarkerTexture;
        sf::Texture secondaryMissMarkerTexture;
        sf::Texture idlePrimaryTargetTexture;
        sf::Texture activePrimaryTargetTexture;
        sf::Texture secondaryTargetTexture;
        sf::Sprite backgroundDefaultSprite;
        sf::Sprite backgroundP1Sprite;
        sf::Sprite backgroundP2Sprite;
        sf::Sprite battleshipSprite;
        sf::Sprite aircraftCarrierSprite;
        sf::Sprite destroyerSprite;
        sf::Sprite submarineSprite;
        sf::Sprite patrolBoatSprite;
        sf::Sprite rowBoatSprite;
        sf::Sprite battleshipSunkSprite;
        sf::Sprite aircraftCarrierSunkSprite;
        sf::Sprite destroyerSunkSprite;
        sf::Sprite submarineSunkSprite;
        sf::Sprite patrolBoatSunkSprite;
        sf::Sprite rowBoatSunkSprite;
        sf::Sprite primaryHitMarkerSprite;
        sf::Sprite primaryMissMarkerSprite;
        sf::Sprite secondaryHitMarkerSprite;
        sf::Sprite secondaryMissMarkerSprite;
        sf::Sprite secondaryTargetSprite;

        Button *surrenderButton;
        Button *instructionsButton;

        vector<Target> targetVector;

        vector<sf::Sprite> primaryMarkersP1Vector;
        vector<sf::Sprite> primaryMarkersP2Vector;
        vector<sf::Sprite> secondaryMarkersP1Vector;
        vector<sf::Sprite> secondaryMarkersP2Vector;
    };
}// namespace screen

#endif// BATTLESHIP_GAMEPLAY_H