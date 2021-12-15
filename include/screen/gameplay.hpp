/**
 * File: gameplay.h
 * Description: Front-end class that defines the behaviour of the Gameplay screen
 */

#ifndef BATTLESHIP_GAMEPLAY_H
#define BATTLESHIP_GAMEPLAY_H

#include "../entity/button.hpp"
#include "../entity/coordinate.hpp"
#include "../entity/grid.hpp"
#include "../entity/shipNames.hpp"
#include "../entity/target.hpp"
#include "screenTemplate.hpp"

#include <SFML/System.hpp>

#include <set>
#include <vector>

using entity::Button;
using entity::Coordinate;
using entity::Grid;
using entity::shipSizes;
using entity::shipsNames;
using entity::SquareType;
using entity::Target;
using std::map;
using std::set;
using std::tuple;
using std::vector;

namespace screen {
    class Gameplay : public ScreenTemplate {
    private:
        /**
         * Default 1 Player background texture
         */
        sf::Texture gameplayDefaultBackgroundTexture;

        /**
         * P1 background texture
         */
        sf::Texture gameplayP1BackgroundTexture;

        /**
         * P2 background texture
         */
        sf::Texture gameplayP2BackgroundTexture;

        /**
         * Idle surrender button texture
         */
        sf::Texture idleSurrenderButtonTexture;

        /**
         * Active surrender button texture
         */
        sf::Texture activeSurrenderButtonTexture;

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
         * Battleship sunk texture
         */
        sf::Texture battleshipSunkTexture;

        /**
         * Aircraft carrier sunk texture
         */
        sf::Texture aircraftCarrierSunkTexture;

        /**
         * Destroyer sunk texture
         */
        sf::Texture destroyerSunkTexture;

        /**
         * Submarine sunk texture
         */
        sf::Texture submarineSunkTexture;

        /**
         * Patrol boat sunk texture
         */
        sf::Texture patrolBoatSunkTexture;

        /**
         * Row boat sunk texture
         */
        sf::Texture rowBoatSunkTexture;

        /**
         * Primary hit marker texture
         */
        sf::Texture primaryHitMarkerTexture;

        /**
         * Primary miss marker texture
         */
        sf::Texture primaryMissMarkerTexture;

        /**
         * Secondary hit marker texture
         */
        sf::Texture secondaryHitMarkerTexture;

        /**
         * Secondary miss marker texture
         */
        sf::Texture secondaryMissMarkerTexture;

        /**
         * Idle Primary target texture
         */
        sf::Texture idlePrimaryTargetTexture;

        /**
         * Active primary target texture
         */
        sf::Texture activePrimaryTargetTexture;

        /**
         * Secondary target texture
         */
        sf::Texture secondaryTargetTexture;

        /**
         * Defauly 1 player background sprite
         */
        sf::Sprite backgroundDefaultSprite;

        /**
         * P1 background sprite
         */
        sf::Sprite backgroundP1Sprite;

        /**
         * P2 backgroudn sprite
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
         * Battleship sunk sprite
         */
        sf::Sprite battleshipSunkSprite;

        /**
         * Aircraft carrier sunk sprite
         */
        sf::Sprite aircraftCarrierSunkSprite;

        /**
         * Destroyer sunk sprite
         */
        sf::Sprite destroyerSunkSprite;

        /**
         * Submarine sunk sprite
         */
        sf::Sprite submarineSunkSprite;

        /**
         * Patrol boat sunk sprite
         */
        sf::Sprite patrolBoatSunkSprite;

        /**
         * Row boat sunksprite
         */
        sf::Sprite rowBoatSunkSprite;

        /**
         * Primary hit marker sprite
         */
        sf::Sprite primaryHitMarkerSprite;

        /**
         * Primary miss marker sprite
         */
        sf::Sprite primaryMissMarkerSprite;

        /**
         * Secondary hit marker sprite
         */
        sf::Sprite secondaryHitMarkerSprite;

        /**
         * Secondary miss marker sprite
         */
        sf::Sprite secondaryMissMarkerSprite;

        /**
         * Secondary target sprite
         */
        sf::Sprite secondaryTargetSprite;

        /**
         * Surrender button 
         */
        Button *surrenderButton;

        /**
         * Instructions button 
         */
        Button *instructionsButton;

        /**
         * Vector of targets
         */
        vector<Target> targetVector;

        /**
         * Vector of P1 primary markers
         */
        vector<sf::Sprite> primaryMarkersP1Vector;

        /**
         * Vector of P2 primary markers
         */
        vector<sf::Sprite> primaryMarkersP2Vector;

        /**
         * Vector of P1 secondary markers
         */
        vector<sf::Sprite> secondaryMarkersP1Vector;

        /**
         * Vector of P2 secondary markers
         */
        vector<sf::Sprite> secondaryMarkersP2Vector;

        /**
         * Map of P1 fleet layout
         */
        map<shipsNames, tuple<Coordinate, bool>> fleetLayoutP1;

        /**
         * Map of P2 fleet layout
         */
        map<shipsNames, tuple<Coordinate, bool>> fleetLayoutP2;

        /**
         * P1 Grid
         */
        static Grid *gridP1;

        /**
         * P2 Grid
         */
        static Grid *gridP2;

        /**
         * Set of grid coordinates used by environment
         */
        set<Coordinate> coordinateSet;

        /**
         * Mouse position vector
         */
        sf::Vector2f mousePosition;

        /**
         * System event
         */
        sf::Event event{};

        /**
         * Generates a set of grid coordinates
         */
        void createCoordinateSet();

        /**
         * Selects a random coordinate from screen::Gameplay::coordinateSet
         */
        Coordinate randomAttack();

        /**
         * Initializes target vector
         */
        void setTargetVector();

        /**
         * Checks if the game is lost
         */
        static bool lost(Grid &grid);

        /**
         * Updates grid markers
         */
        void updateGridMarkers(SquareType attack, Coordinate coordinate);

        /**
         * Resets grid markers
         */
        void resetGridMarkers();

        /**
         * Updates secondary traget
         */
        void updateSecondaryTarget(Coordinate coordinate);

        /**
         * Sleeps the process (works for windows and unix-based systems)
         */
        static void sleepMS();

        /**
         * Updates grid state
         */
        void updateGrid(Coordinate coordinate, sf::RenderWindow &grid);

        /**
         * Sets the fleet layout of the current player
         */
        void setFleetLayout(map<shipsNames, tuple<Coordinate, bool>> &fleetLayout);

        /**
         * Calls helpers::updateMousePosition(), Button::updateButtonState(), Target::updateTargetState(), Grid::getShips(), and Gameplay::setFleetLayout()
         */
        void update(sf::RenderWindow &gui, sf::Vector2f mousePosition);

        /**
         * Polls for system events
         */
        void poll(sf::RenderWindow &gui);

        /**
         * Renders ship status
         */
        void renderShipStatus(Grid &grid, sf::RenderWindow &gui);

        /**
         * Renders all sprites
         */
        void render(sf::RenderWindow &gui);

        /**
         * The sleep time after a player attacks in milliseconds
         */
        static constexpr int sleepTimeMS = 400;

    public:
        /**
         * Constructor
         */
        Gameplay();

        /**
         * Copy constructor
         */
        Gameplay(const Gameplay &source);

        /**
         * Destructor
         */
        ~Gameplay() override;

        /**
         * Overloaded assignment operator
         */
        Gameplay &operator=(const Gameplay &source);

        /**
         * Initializes P1 grid
         */
        static void setP1Grid(const map<shipsNames, tuple<Coordinate, bool>> &ships);

        /**
         * Initializes P2 grid
         */
        static void setP2Grid(const map<shipsNames, tuple<Coordinate, bool>> &ships);

        /**
         * Overridden run method of screenTemplate
         */
        void run(sf::RenderWindow &gui) override;
    };
}// namespace screen

#endif// BATTLESHIP_GAMEPLAY_H