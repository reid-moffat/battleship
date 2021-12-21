/**
 * File: fleetPlacement.cpp
 * Description: Front-end class that defines the behaviour of the Fleet Placement screens
 */

#include "fleetPlacement.hpp"
#include "../helpers.hpp"
#include "gameplay.hpp"

using screen::FleetPlacement;
using std::get;

FleetPlacement* FleetPlacement::instance = nullptr;

FleetPlacement::FleetPlacement() : ScreenTemplate() {
    loadTexture(this->fleetPlacementDefaultBackgroundTexture, "fleetPlacement/FleetPlacementBackground.png");
    loadTexture(this->fleetPlacementP1BackgroundTexture, "fleetPlacement/FleetPlacementP1Background.png");
    loadTexture(this->fleetPlacementP2BackgroundTexture, "fleetPlacement/FleetPlacementP2Background.png");

    loadTexture(this->idleReadyButtonTexture, "fleetPlacement/IdleReadyButton.png");
    loadTexture(this->activeReadyButtonTexture, "fleetPlacement/ActiveReadyButton.png");
    loadTexture(this->idleRandomizeButtonTexture, "fleetPlacement/IdleRandomizeButton.png");
    loadTexture(this->activeRandomizeButtonTexture, "fleetPlacement/ActiveRandomizeButton.png");
    loadTexture(this->idleInstructionsButtonTexture, "fleetPlacement/IdleInstructionsButton.png");
    loadTexture(this->activeInstructionsButtonTexture, "fleetPlacement/ActiveInstructionsButton.png");

    loadTexture(this->battleshipTexture, "fleetPlacement/BattleShip.png");
    loadTexture(this->aircraftCarrierTexture, "fleetPlacement/AircraftCarrier.png");
    loadTexture(this->destroyerTexture, "fleetPlacement/Destroyer.png");
    loadTexture(this->submarineTexture, "fleetPlacement/Submarine.png");
    loadTexture(this->patrolBoatTexture, "fleetPlacement/PatrolBoat.png");
    loadTexture(this->rowBoatTexture, "fleetPlacement/RowBoat.png");

    setSprite(sf::Vector2f(0, 0), sf::Vector2f(5, 5), this->fleetPlacementDefaultBackgroundTexture, this->backgroundDefaultSprite);
    setSprite(sf::Vector2f(0, 0), sf::Vector2f(5, 5), this->fleetPlacementP1BackgroundTexture, this->backgroundP1Sprite);
    setSprite(sf::Vector2f(0, 0), sf::Vector2f(5, 5), this->fleetPlacementP2BackgroundTexture, this->backgroundP2Sprite);

    setSprite(sf::Vector2f(21 * 5, 84 * 5), sf::Vector2f(5, 5), this->battleshipTexture, this->battleshipSprite);
    setSprite(sf::Vector2f(42 * 5, 92 * 5), sf::Vector2f(5, 5), this->aircraftCarrierTexture, this->aircraftCarrierSprite);
    setSprite(sf::Vector2f(61 * 5, 100 * 5), sf::Vector2f(5, 5), this->destroyerTexture, this->destroyerSprite);
    setSprite(sf::Vector2f(61 * 5, 35 * 5), sf::Vector2f(5, 5), this->submarineTexture, this->submarineSprite);
    setSprite(sf::Vector2f(42 * 5, 43 * 5), sf::Vector2f(5, 5), this->patrolBoatTexture, this->patrolBoatSprite);
    setSprite(sf::Vector2f(21 * 5, 51 * 5), sf::Vector2f(5, 5), this->rowBoatTexture, this->rowBoatSprite);

    this->readyButton = new Button(sf::Vector2f(320 * 5, 124 * 5), sf::Vector2f(5, 5), this->idleReadyButtonTexture, this->activeReadyButtonTexture);
    this->randomizeButton = new Button(sf::Vector2f(328 * 5, 76 * 5), sf::Vector2f(5, 5), this->idleRandomizeButtonTexture, this->activeRandomizeButtonTexture);
    this->instructionsButton = new Button(sf::Vector2f(352 * 5, 12 * 5), sf::Vector2f(5, 5), this->idleInstructionsButtonTexture, this->activeInstructionsButtonTexture);

    this->layoutGenerated = false;
}

void FleetPlacement::addCoord(vector<Coordinate> &coordinates, int x, int y) {
    // If a ship is on the edge, adjacent squares don't exist and that is ok (don't throw an exception)
    if (x >= 0 && x <= 9 && y >= 0 && y <= 9) {
        coordinates.emplace_back(Coordinate(x, y));
    }
}


void FleetPlacement::randomize() {
    // Start with all false values
    bool grid[10][10];
    for (auto &row : grid) {
        for (bool &square : row) {
            square = false;
        }
    }

    // Find spots for the ships (start with the big ships to speed it up)
    static shipNames allShips[6] = {
            shipNames::BATTLESHIP,
            shipNames::AIRCRAFT_CARRIER,
            shipNames::DESTROYER,
            shipNames::SUBMARINE,
            shipNames::PATROL_BOAT,
            shipNames::ROW_BOAT,
    };
    for (shipNames ship : allShips) {
        int size = shipSize(ship);
        while (true) {
            bool horizontal = randomInt(0, 1) % 2 != 0;// Whether the ship is horizontal or vertical

            // Determine a random x and y position for the ship (it will be on the board, but might already be occupied)
            const int maxBoardIndex = 9;       // The maximum coordinate index on the board (since there are 10 squares)
            const int maxShipStart = 10 - size;// The maximum coordinate index to start the ship at so that it fits on the board
            int x = randomInt(0, horizontal ? maxShipStart : maxBoardIndex);
            int y = randomInt(0, horizontal ? maxBoardIndex : maxShipStart);

            // Create a list of square to check
            vector<Coordinate> shipSquares;// Squares occupied by this ship and adjacent ones

            if (horizontal) {
                for (int i = 0; i < size; ++i) {
                    addCoord(shipSquares, x + i, y);// Actual ship
                }
                addCoord(shipSquares, x - 1, y);// Square left of the leftmost part
                for (int i = 0; i < size; ++i) {
                    addCoord(shipSquares, x + i, y - 1);// 1 square above
                    addCoord(shipSquares, x + i, y + 1);// 1 square below
                }
                addCoord(shipSquares, x + size, y);// Square right of the rightmost part
            } else {
                for (int i = 0; i < size; ++i) {
                    addCoord(shipSquares, x, y + i);// Actual ship
                }
                addCoord(shipSquares, x, y - 1);// Square above the topmost part
                for (int i = 0; i < size; ++i) {
                    addCoord(shipSquares, x - 1, y + i);// 1 square left
                    addCoord(shipSquares, x + 1, y + i);// 1 square right
                }
                addCoord(shipSquares, x, y + size);// Square below the bottom part
            }

            // Check if all the ship squares are available
            bool invalid = false;
            for (Coordinate c : shipSquares) {
                if (grid[c.getY()][c.getX()]) {
                    invalid = true;
                    break;
                }
            }
            if (invalid) continue;// If not, try again

            // The ship is valid; now place it down
            ships[ship] = {shipSquares.at(0), horizontal};// Ship coordinate and orientation
            for (int i = 0; i < size; ++i) {
                // Only set the actual squares this ship is occupying
                // It is ok if there is only one square in between ships
                Coordinate curr = shipSquares.at(i);
                grid[curr.getY()][curr.getX()] = true;
            }
            break;
        }
    }
}

void FleetPlacement::updateFleetLayout() {
    if (get<1>(this->ships[shipNames::BATTLESHIP]) == 1) {
        this->battleshipSprite.setPosition(sf::Vector2f((224 + (get<0>(this->ships[shipNames::BATTLESHIP]).getX() * 16)) * 5,
                                                        (28 + (get<0>(this->ships[shipNames::BATTLESHIP]).getY() * 16)) * 5));
        this->battleshipSprite.setRotation(90.f);
    } else {
        this->battleshipSprite.setPosition(sf::Vector2f((128 + (get<0>(this->ships[shipNames::BATTLESHIP]).getX() * 16)) * 5,
                                                        (28 + (get<0>(this->ships[shipNames::BATTLESHIP]).getY() * 16)) * 5));
        this->battleshipSprite.setRotation(0);
    }

    if (get<1>(this->ships[shipNames::AIRCRAFT_CARRIER]) == 1) {
        this->aircraftCarrierSprite.setPosition(sf::Vector2f((208 + (get<0>(this->ships[shipNames::AIRCRAFT_CARRIER]).getX() * 16)) * 5,
                                                             (28 + (get<0>(this->ships[shipNames::AIRCRAFT_CARRIER]).getY() * 16)) * 5));
        this->aircraftCarrierSprite.setRotation(90.f);
    } else {
        this->aircraftCarrierSprite.setPosition(sf::Vector2f((128 + (get<0>(this->ships[shipNames::AIRCRAFT_CARRIER]).getX() * 16)) * 5,
                                                             (28 + (get<0>(this->ships[shipNames::AIRCRAFT_CARRIER]).getY() * 16)) * 5));
        this->aircraftCarrierSprite.setRotation(0);
    }

    if (get<1>(this->ships[shipNames::DESTROYER]) == 1) {
        this->destroyerSprite.setPosition(sf::Vector2f((192 + (get<0>(this->ships[shipNames::DESTROYER]).getX() * 16)) * 5,
                                                       (28 + (get<0>(this->ships[shipNames::DESTROYER]).getY() * 16)) * 5));
        this->destroyerSprite.setRotation(90.f);
    } else {
        this->destroyerSprite.setPosition(sf::Vector2f((128 + (get<0>(this->ships[shipNames::DESTROYER]).getX() * 16)) * 5,
                                                       (28 + (get<0>(this->ships[shipNames::DESTROYER]).getY() * 16)) * 5));
        this->destroyerSprite.setRotation(0);
    }

    if (get<1>(this->ships[shipNames::SUBMARINE]) == 1) {
        this->submarineSprite.setPosition(sf::Vector2f((176 + (get<0>(this->ships[shipNames::SUBMARINE]).getX() * 16)) * 5,
                                                       (28 + (get<0>(this->ships[shipNames::SUBMARINE]).getY() * 16)) * 5));
        this->submarineSprite.setRotation(90.f);
    } else {
        this->submarineSprite.setPosition(sf::Vector2f((128 + (get<0>(this->ships[shipNames::SUBMARINE]).getX() * 16)) * 5,
                                                       (28 + (get<0>(this->ships[shipNames::SUBMARINE]).getY() * 16)) * 5));
        this->submarineSprite.setRotation(0);
    }

    if (get<1>(this->ships[shipNames::PATROL_BOAT]) == 1) {
        this->patrolBoatSprite.setPosition(sf::Vector2f((160 + (get<0>(this->ships[shipNames::PATROL_BOAT]).getX() * 16)) * 5,
                                                        (28 + (get<0>(this->ships[shipNames::PATROL_BOAT]).getY() * 16)) * 5));
        this->patrolBoatSprite.setRotation(90.f);
    } else {
        this->patrolBoatSprite.setPosition(sf::Vector2f((128 + (get<0>(this->ships[shipNames::PATROL_BOAT]).getX() * 16)) * 5,
                                                        (28 + (get<0>(this->ships[shipNames::PATROL_BOAT]).getY() * 16)) * 5));
        this->patrolBoatSprite.setRotation(0);
    }

    if (get<1>(this->ships[shipNames::ROW_BOAT]) == 1) {
        this->rowBoatSprite.setPosition(sf::Vector2f((144 + (get<0>(this->ships[shipNames::ROW_BOAT]).getX() * 16)) * 5,
                                                     (28 + (get<0>(this->ships[shipNames::ROW_BOAT]).getY() * 16)) * 5));
        this->rowBoatSprite.setRotation(90.0);
    } else {
        this->rowBoatSprite.setPosition(sf::Vector2f((128 + (get<0>(this->ships[shipNames::ROW_BOAT]).getX() * 16)) * 5,
                                                     (28 + (get<0>(this->ships[shipNames::ROW_BOAT]).getY() * 16)) * 5));
        this->rowBoatSprite.setRotation(0);
    }
}

void FleetPlacement::resetFleetLayout() {
    this->battleshipSprite.setPosition(sf::Vector2f(21 * 5, 84 * 5));
    this->battleshipSprite.setRotation(0);

    this->aircraftCarrierSprite.setPosition(sf::Vector2f(42 * 5, 92 * 5));
    this->aircraftCarrierSprite.setRotation(0);

    this->destroyerSprite.setPosition(sf::Vector2f(61 * 5, 100 * 5));
    this->destroyerSprite.setRotation(0);

    this->submarineSprite.setPosition(sf::Vector2f(61 * 5, 35 * 5));
    this->submarineSprite.setRotation(0);

    this->patrolBoatSprite.setPosition(sf::Vector2f(42 * 5, 43 * 5));
    this->patrolBoatSprite.setRotation(0);

    this->rowBoatSprite.setPosition(sf::Vector2f(21 * 5, 51 * 5));
    this->rowBoatSprite.setRotation(0);
}

void FleetPlacement::update() {
    sf::Vector2f mousePosition = State::getMousePosition();
    this->readyButton->updateButtonState(mousePosition);
    this->randomizeButton->updateButtonState(mousePosition);
    this->instructionsButton->updateButtonState(mousePosition);
}

void FleetPlacement::poll(sf::RenderWindow &gui) {
    while (gui.pollEvent(this->event)) {
        switch (this->event.type) {

            case sf::Event::Closed:
                gui.close();
                break;

            case sf::Event::MouseButtonReleased:
                if ((event.mouseButton.button == sf::Mouse::Left) && (this->readyButton->getButtonState())) {
                    if (State::gameMode == State::GameMode::SINGLE_PLAYER) {
                        Gameplay::setP1Grid(ships);
                        this->resetFleetLayout();
                        this->layoutGenerated = false;
                        this->randomize();
                        Gameplay::setP2Grid(ships);
                        State::changeScreen(Screens::GAMEPLAY);
                        break;
                    } else {
                        if (State::player == State::Player::P1) {
                            Gameplay::setP1Grid(ships);
                            this->resetFleetLayout();
                            this->layoutGenerated = false;
                            State::player = State::Player::P2;
                            State::changeScreen(Screens::INTERMEDIARY);
                            break;
                        } else {
                            Gameplay::setP2Grid(ships);
                            this->resetFleetLayout();
                            this->layoutGenerated = false;
                            State::player = State::Player::P1;
                            State::changeScreen(Screens::INTERMEDIARY);
                            break;
                        }
                    }
                } else if ((event.mouseButton.button == sf::Mouse::Left) && (this->randomizeButton->getButtonState())) {
                    this->randomize();
                    this->updateFleetLayout();
                    this->layoutGenerated = true;
                    break;
                } else if ((event.mouseButton.button == sf::Mouse::Left) && (this->instructionsButton->getButtonState())) {
                    State::changeScreen(Screens::INSTRUCTIONS);
                    break;
                } else {
                    break;
                }

            default:
                break;
        }
    }
}

void FleetPlacement::render(sf::RenderWindow &gui) {
    gui.clear();

    if (State::gameMode == State::SINGLE_PLAYER) {
        gui.draw(this->backgroundDefaultSprite);
    } else {
        if (State::player == State::Player::P1) {
            gui.draw(this->backgroundP1Sprite);
        } else {
            gui.draw(this->backgroundP2Sprite);
        }
    }

    if (layoutGenerated) {
        readyButton->render(gui);
    }

    randomizeButton->render(gui);
    instructionsButton->render(gui);

    gui.draw(this->battleshipSprite);
    gui.draw(this->aircraftCarrierSprite);
    gui.draw(this->destroyerSprite);
    gui.draw(this->submarineSprite);
    gui.draw(this->patrolBoatSprite);
    gui.draw(this->rowBoatSprite);

    if (State::getCurrentScreen() == Screens::FLEET_PLACEMENT) {
        gui.display();
    }
}

void FleetPlacement::run() {
    this->update();
    this->poll(*State::gui);
    this->render(*State::gui);
}

FleetPlacement &screen::FleetPlacement::getInstance() {
    if (instance == nullptr) {
        instance = new FleetPlacement();
    }
    return *instance;
}
