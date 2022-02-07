/**
 * Front-end class that defines the behaviour of the Fleet Placement screens
 */

#include "fleetPlacement.hpp"
#include "gameplay.hpp"

using screen::FleetPlacement;
using std::get;

std::unique_ptr<FleetPlacement> FleetPlacement::instance = nullptr;

FleetPlacement::FleetPlacement() : ScreenTemplate() {
    const vector<string> texturePaths = {"fleetPlacement/FleetPlacementBackground.png", "fleetPlacement/FleetPlacementP1Background.png",
                                         "fleetPlacement/FleetPlacementP2Background.png",
                                         "fleetPlacement/IdleReadyButton.png", "fleetPlacement/ActiveReadyButton.png",
                                         "fleetPlacement/IdleRandomizeButton.png", "fleetPlacement/ActiveRandomizeButton.png",
                                         "fleetPlacement/IdleInstructionsButton.png", "fleetPlacement/ActiveInstructionsButton.png",
                                         "fleetPlacement/BattleShip.png", "fleetPlacement/AircraftCarrier.png",
                                         "fleetPlacement/Destroyer.png", "fleetPlacement/Submarine.png",
                                         "fleetPlacement/PatrolBoat.png", "fleetPlacement/RowBoat.png"};
    const vector<sprite> sprites = {{sf::Vector2f(0, 0), sf::Vector2f(5, 5), BackgroundDefault_},
                                    {sf::Vector2f(0, 0), sf::Vector2f(5, 5), BackgroundP1_},
                                    {sf::Vector2f(0, 0), sf::Vector2f(5, 5), BackgroundP2_},
                                    {sf::Vector2f(21 * 5, 84 * 5), sf::Vector2f(5, 5), Battleship_},
                                    {sf::Vector2f(42 * 5, 92 * 5), sf::Vector2f(5, 5), AircraftCarrier_},
                                    {sf::Vector2f(61 * 5, 100 * 5), sf::Vector2f(5, 5), Destroyer_},
                                    {sf::Vector2f(61 * 5, 35 * 5), sf::Vector2f(5, 5), Submarine_},
                                    {sf::Vector2f(42 * 5, 43 * 5), sf::Vector2f(5, 5), PatrolBoat_},
                                    {sf::Vector2f(21 * 5, 51 * 5), sf::Vector2f(5, 5), RowBoat_}};
    const vector<button> buttons = {{sf::Vector2f(320 * 5, 124 * 5), sf::Vector2f(5, 5), IdleReadyButton, ActiveReadyButton},
                                    {sf::Vector2f(328 * 5, 76 * 5), sf::Vector2f(5, 5), IdleRandomizeButton, ActiveRandomizeButton},
                                    {sf::Vector2f(352 * 5, 12 * 5), sf::Vector2f(5, 5), IdleInstructionsButton, ReadyInstructionsButton}};

    this->resources = ScreenResourceManager(texturePaths, sprites, buttons);

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
    // TODO: Move this to a field
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
    sf::Sprite &battleship = resources.getSprite(Battleship);
    sf::Sprite &aircraftCarrier = resources.getSprite(AircraftCarrier);
    sf::Sprite &destroyer = resources.getSprite(Destroyer);
    sf::Sprite &submarine = resources.getSprite(Submarine);
    sf::Sprite &patrolBoat = resources.getSprite(PatrolBoat);
    sf::Sprite &rowBoat = resources.getSprite(RowBoat);

    if (get<1>(this->ships[shipNames::BATTLESHIP]) == 1) {
        battleship.setPosition(sf::Vector2f((224 + (get<0>(this->ships[shipNames::BATTLESHIP]).getX() * 16)) * 5,
                                            (28 + (get<0>(this->ships[shipNames::BATTLESHIP]).getY() * 16)) * 5));
        battleship.setRotation(90.f);
    } else {
        battleship.setPosition(sf::Vector2f((128 + (get<0>(this->ships[shipNames::BATTLESHIP]).getX() * 16)) * 5,
                                            (28 + (get<0>(this->ships[shipNames::BATTLESHIP]).getY() * 16)) * 5));
        battleship.setRotation(0);
    }

    if (get<1>(this->ships[shipNames::AIRCRAFT_CARRIER]) == 1) {
        aircraftCarrier.setPosition(sf::Vector2f((208 + (get<0>(this->ships[shipNames::AIRCRAFT_CARRIER]).getX() * 16)) * 5,
                                                 (28 + (get<0>(this->ships[shipNames::AIRCRAFT_CARRIER]).getY() * 16)) * 5));
        aircraftCarrier.setRotation(90.f);
    } else {
        aircraftCarrier.setPosition(sf::Vector2f((128 + (get<0>(this->ships[shipNames::AIRCRAFT_CARRIER]).getX() * 16)) * 5,
                                                 (28 + (get<0>(this->ships[shipNames::AIRCRAFT_CARRIER]).getY() * 16)) * 5));
        aircraftCarrier.setRotation(0);
    }

    if (get<1>(this->ships[shipNames::DESTROYER]) == 1) {
        destroyer
                .setPosition(sf::Vector2f((192 + (get<0>(this->ships[shipNames::DESTROYER]).getX() * 16)) * 5,
                                          (28 + (get<0>(this->ships[shipNames::DESTROYER]).getY() * 16)) * 5));
        destroyer.setRotation(90.f);
    } else {
        destroyer.setPosition(sf::Vector2f((128 + (get<0>(this->ships[shipNames::DESTROYER]).getX() * 16)) * 5,
                                           (28 + (get<0>(this->ships[shipNames::DESTROYER]).getY() * 16)) * 5));
        destroyer.setRotation(0);
    }

    if (get<1>(this->ships[shipNames::SUBMARINE]) == 1) {
        submarine.setPosition(sf::Vector2f((176 + (get<0>(this->ships[shipNames::SUBMARINE]).getX() * 16)) * 5,
                                           (28 + (get<0>(this->ships[shipNames::SUBMARINE]).getY() * 16)) * 5));
        submarine.setRotation(90.f);
    } else {
        submarine.setPosition(sf::Vector2f((128 + (get<0>(this->ships[shipNames::SUBMARINE]).getX() * 16)) * 5,
                                           (28 + (get<0>(this->ships[shipNames::SUBMARINE]).getY() * 16)) * 5));
        submarine.setRotation(0);
    }

    if (get<1>(this->ships[shipNames::PATROL_BOAT]) == 1) {
        patrolBoat.setPosition(sf::Vector2f((160 + (get<0>(this->ships[shipNames::PATROL_BOAT]).getX() * 16)) * 5,
                                            (28 + (get<0>(this->ships[shipNames::PATROL_BOAT]).getY() * 16)) * 5));
        patrolBoat.setRotation(90.f);
    } else {
        patrolBoat.setPosition(sf::Vector2f((128 + (get<0>(this->ships[shipNames::PATROL_BOAT]).getX() * 16)) * 5,
                                            (28 + (get<0>(this->ships[shipNames::PATROL_BOAT]).getY() * 16)) * 5));
        patrolBoat.setRotation(0);
    }

    if (get<1>(this->ships[shipNames::ROW_BOAT]) == 1) {
        rowBoat.setPosition(sf::Vector2f((144 + (get<0>(this->ships[shipNames::ROW_BOAT]).getX() * 16)) * 5,
                                         (28 + (get<0>(this->ships[shipNames::ROW_BOAT]).getY() * 16)) * 5));
        rowBoat.setRotation(90.0);
    } else {
        rowBoat.setPosition(sf::Vector2f((128 + (get<0>(this->ships[shipNames::ROW_BOAT]).getX() * 16)) * 5,
                                         (28 + (get<0>(this->ships[shipNames::ROW_BOAT]).getY() * 16)) * 5));
        rowBoat.setRotation(0);
    }
}

void FleetPlacement::resetFleetLayout() {
    resources.getSprite(Battleship).setPosition(sf::Vector2f(21 * 5, 84 * 5));
    resources.getSprite(Battleship).setRotation(0);

    resources.getSprite(AircraftCarrier).setPosition(sf::Vector2f(42 * 5, 92 * 5));
    resources.getSprite(AircraftCarrier).setRotation(0);

    resources.getSprite(Destroyer).setPosition(sf::Vector2f(61 * 5, 100 * 5));
    resources.getSprite(Destroyer).setRotation(0);

    resources.getSprite(Submarine).setPosition(sf::Vector2f(61 * 5, 35 * 5));
    resources.getSprite(Submarine).setRotation(0);

    resources.getSprite(PatrolBoat).setPosition(sf::Vector2f(42 * 5, 43 * 5));
    resources.getSprite(PatrolBoat).setRotation(0);

    resources.getSprite(RowBoat).setPosition(sf::Vector2f(21 * 5, 51 * 5));
    resources.getSprite(RowBoat).setRotation(0);
}

void FleetPlacement::update() {
    sf::Vector2f mousePosition = State::getMousePosition();

    resources.getButton(Ready).updateButtonState(mousePosition);
    resources.getButton(Randomize).updateButtonState(mousePosition);
    resources.getButton(Instructions).updateButtonState(mousePosition);
}

void FleetPlacement::poll() {
    sf::RenderWindow &gui = *State::gui;
    sf::Event &event = State::event;

    while (gui.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                gui.close();
                break;
            case sf::Event::MouseButtonReleased:
                if ((event.mouseButton.button == sf::Mouse::Left) && (resources.getButton(Ready).getButtonState())) {
                    Gameplay *gameplayInstance = &Gameplay::getInstance();
                    if (State::gameMode == State::GameMode::SINGLE_PLAYER) {
                        gameplayInstance->setP1Grid(ships);
                        this->resetFleetLayout();
                        this->layoutGenerated = false;
                        this->randomize();
                        gameplayInstance->setP2Grid(ships);
                        State::changeScreen(Screens::GAMEPLAY);
                        break;
                    } else {
                        if (State::player == State::Player::P1) {
                            gameplayInstance->setP1Grid(ships);
                            this->resetFleetLayout();
                            this->layoutGenerated = false;
                            State::player = State::Player::P2;
                            State::changeScreen(Screens::INTERMEDIARY);
                            break;
                        } else {
                            gameplayInstance->setP2Grid(ships);
                            this->resetFleetLayout();
                            this->layoutGenerated = false;
                            State::player = State::Player::P1;
                            State::changeScreen(Screens::INTERMEDIARY);
                            break;
                        }
                    }
                } else if ((event.mouseButton.button == sf::Mouse::Left) && (resources.getButton(Randomize).getButtonState())) {
                    this->randomize();
                    this->updateFleetLayout();
                    this->layoutGenerated = true;
                    break;
                } else if ((event.mouseButton.button == sf::Mouse::Left) && (resources.getButton(Instructions).getButtonState())) {
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

void FleetPlacement::render() {
    sf::RenderWindow &gui = *State::gui;
    gui.clear();

    if (State::gameMode == State::SINGLE_PLAYER) {
        gui.draw(resources.getSprite(BackgroundDefault));
    } else {
        if (State::player == State::Player::P1) {
            gui.draw(resources.getSprite(BackgroundP1));
        } else {
            gui.draw(resources.getSprite(BackgroundP2));
        }
    }

    if (layoutGenerated) {
        resources.getButton(Ready).render(gui);
    }

    resources.getButton(Randomize).render(gui);
    resources.getButton(Instructions).render(gui);

    gui.draw(resources.getSprite(Battleship));
    gui.draw(resources.getSprite(AircraftCarrier));
    gui.draw(resources.getSprite(Destroyer));
    gui.draw(resources.getSprite(Submarine));
    gui.draw(resources.getSprite(PatrolBoat));
    gui.draw(resources.getSprite(RowBoat));

    if (State::getCurrentScreen() == Screens::FLEET_PLACEMENT) {
        gui.display();
    }
}

FleetPlacement &screen::FleetPlacement::getInstance() {
    if (instance == nullptr) {
        instance.reset(new FleetPlacement());
    }
    return *instance;
}
