/**
 * Stores a player's 10-by-10 grid and their ships
 */

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "../helpers.hpp"
#include "gameplay.hpp"

using entity::SquareType;
using screen::Gameplay;
using std::get;

// TODO: re-design the grid implementation
Grid *Gameplay::gridP1 = new Grid();
Grid *Gameplay::gridP2 = new Grid();
map<shipNames, tuple<Coordinate, bool>> Gameplay::fleetLayoutP1 = *new map<shipNames, tuple<Coordinate, bool>>;
map<shipNames, tuple<Coordinate, bool>> Gameplay::fleetLayoutP2 = *new map<shipNames, tuple<Coordinate, bool>>;

Gameplay *Gameplay::instance = nullptr;

Gameplay::Gameplay() : ScreenTemplate() {
    loadTexture(this->gameplayDefaultBackgroundTexture, "gameplay/GameplayBackground.png");
    loadTexture(this->gameplayP1BackgroundTexture, "gameplay/GameplayP1Background.png");
    loadTexture(this->gameplayP2BackgroundTexture, "gameplay/GameplayP2Background.png");

    loadTexture(this->idleSurrenderButtonTexture, "gameplay/IdleSurrenderButton.png");
    loadTexture(this->activeSurrenderButtonTexture, "gameplay/ActiveSurrenderButton.png");
    loadTexture(this->idleInstructionsButtonTexture, "gameplay/IdleInstructionsButton.png");
    loadTexture(this->activeInstructionsButtonTexture, "gameplay/ActiveInstructionsButton.png");

    loadTexture(this->battleshipTexture, "gameplay/BattleShip.png");
    loadTexture(this->aircraftCarrierTexture, "gameplay/AircraftCarrier.png");
    loadTexture(this->destroyerTexture, "gameplay/Destroyer.png");
    loadTexture(this->submarineTexture, "gameplay/Submarine.png");
    loadTexture(this->patrolBoatTexture, "gameplay/PatrolBoat.png");
    loadTexture(this->rowBoatTexture, "gameplay/RowBoat.png");

    loadTexture(this->battleshipSunkTexture, "gameplay/BattleShipSunk.png");
    loadTexture(this->aircraftCarrierSunkTexture, "gameplay/AircraftCarrierSunk.png");
    loadTexture(this->destroyerSunkTexture, "gameplay/DestroyerSunk.png");
    loadTexture(this->submarineSunkTexture, "gameplay/SubmarineSunk.png");
    loadTexture(this->patrolBoatSunkTexture, "gameplay/PatrolBoatSunk.png");
    loadTexture(this->rowBoatSunkTexture, "gameplay/RowBoatSunk.png");

    loadTexture(this->primaryHitMarkerTexture, "gameplay/PrimaryHitMarker.png");
    loadTexture(this->primaryMissMarkerTexture, "gameplay/PrimaryMissMarker.png");
    loadTexture(this->secondaryHitMarkerTexture, "gameplay/SecondaryHitMarker.png");
    loadTexture(this->secondaryMissMarkerTexture, "gameplay/SecondaryMissMarker.png");

    Target::initializeTextures();
    loadTexture(this->secondaryTargetTexture, "gameplay/SecondaryTarget.png");

    setSprite(sf::Vector2f(0, 0), sf::Vector2f(5, 5), this->gameplayDefaultBackgroundTexture, this->backgroundDefaultSprite);
    setSprite(sf::Vector2f(0, 0), sf::Vector2f(5, 5), this->gameplayP1BackgroundTexture, this->backgroundP1Sprite);
    setSprite(sf::Vector2f(0, 0), sf::Vector2f(5, 5), this->gameplayP2BackgroundTexture, this->backgroundP2Sprite);

    setSprite(sf::Vector2f(330 * 5, 113 * 5), sf::Vector2f(5, 5), this->battleshipSunkTexture, this->battleshipSunkSprite);
    setSprite(sf::Vector2f(348 * 5, 117 * 5), sf::Vector2f(5, 5), this->aircraftCarrierSunkTexture, this->aircraftCarrierSunkSprite);
    setSprite(sf::Vector2f(348 * 5, 75 * 5), sf::Vector2f(5, 5), this->destroyerSunkTexture, this->destroyerSunkSprite);
    setSprite(sf::Vector2f(330 * 5, 79 * 5), sf::Vector2f(5, 5), this->submarineSunkTexture, this->submarineSunkSprite);
    setSprite(sf::Vector2f(330 * 5, 53 * 5), sf::Vector2f(5, 5), this->patrolBoatSunkTexture, this->patrolBoatSunkSprite);
    setSprite(sf::Vector2f(348 * 5, 57 * 5), sf::Vector2f(5, 5), this->rowBoatSunkTexture, this->rowBoatSunkSprite);

    this->battleshipSprite.setTexture(this->battleshipTexture);
    this->battleshipSprite.setScale(sf::Vector2f(5, 5));
    this->aircraftCarrierSprite.setTexture(this->aircraftCarrierTexture);
    this->aircraftCarrierSprite.setScale(sf::Vector2f(5, 5));
    this->destroyerSprite.setTexture(this->destroyerTexture);
    this->destroyerSprite.setScale(sf::Vector2f(5, 5));
    this->submarineSprite.setTexture(this->submarineTexture);
    this->submarineSprite.setScale(sf::Vector2f(5, 5));
    this->patrolBoatSprite.setTexture(this->patrolBoatTexture);
    this->patrolBoatSprite.setScale(sf::Vector2f(5, 5));
    this->rowBoatSprite.setTexture(this->rowBoatTexture);
    this->rowBoatSprite.setScale(sf::Vector2f(5, 5));

    this->primaryHitMarkerSprite.setTexture(this->primaryHitMarkerTexture);
    this->primaryHitMarkerSprite.setScale(sf::Vector2f(5, 5));
    this->primaryMissMarkerSprite.setTexture(this->primaryMissMarkerTexture);
    this->primaryMissMarkerSprite.setScale(sf::Vector2f(5, 5));
    this->secondaryHitMarkerSprite.setTexture(this->secondaryHitMarkerTexture);
    this->secondaryHitMarkerSprite.setScale(sf::Vector2f(5, 5));
    this->secondaryMissMarkerSprite.setTexture(this->secondaryMissMarkerTexture);
    this->secondaryMissMarkerSprite.setScale(sf::Vector2f(5, 5));

    this->secondaryTargetSprite.setTexture(this->secondaryTargetTexture);
    this->secondaryTargetSprite.setScale(sf::Vector2f(5, 5));

    this->surrenderButton = new Button(sf::Vector2f(320 * 5, 12 * 5), sf::Vector2f(5, 5), this->idleSurrenderButtonTexture, this->activeSurrenderButtonTexture);
    this->instructionsButton = new Button(sf::Vector2f(352 * 5, 12 * 5), sf::Vector2f(5, 5), this->idleInstructionsButtonTexture, this->activeInstructionsButtonTexture);

    this->setTargetVector();
    this->createCoordinateSet();
}

void Gameplay::setP1Grid(const map<shipNames, tuple<Coordinate, bool>> &ships) {
    Gameplay::gridP1 = new Grid(ships);
    Gameplay::fleetLayoutP1 = gridP1->getShips();
}

void Gameplay::setP2Grid(const map<shipNames, tuple<Coordinate, bool>> &ships) {
    Gameplay::gridP2 = new Grid(ships);
    Gameplay::fleetLayoutP2 = gridP2->getShips();
}

void Gameplay::createCoordinateSet() {
    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 10; x++) {
            Coordinate coordinate(x, y);
            this->coordinateSet.insert(coordinate);
        }
    }
}

Coordinate Gameplay::randomAttack() {
    // Generate a random index
    int randGen = randomInt(0, this->coordinateSet.size() - 1);
    // Find the random coordinate
    auto itr = this->coordinateSet.begin();
    advance(itr, randGen);
    // Remove element from coordinateSet
    this->coordinateSet.erase(itr);
    return *itr;
}

void Gameplay::setTargetVector() {
    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 10; x++) {
            Coordinate coordinate(x, y);
            Target target(coordinate, sf::Vector2f(((128 + (x * 16)) * 5), ((28 + (y * 16)) * 5)), sf::Vector2f(5, 5));
            targetVector.push_back(target);
        }
    }
}

bool Gameplay::lost(Grid &grid) {
    map<shipNames, bool> shipStatus = grid.getShipStatus();
    return std::all_of(shipStatus.cbegin(), shipStatus.cend(), [](const auto &ship) { return ship.second; });
}

void Gameplay::updateGridMarkers(SquareType attack, Coordinate coordinate) {
    if (State::gameMode == State::GameMode::SINGLE_PLAYER) {
        if (State::player == State::Player::P1) {
            if (attack == SquareType::WATER) {
                this->primaryMissMarkerSprite.setPosition(sf::Vector2f(((128 + (coordinate.getX() * 16)) * 5), ((28 + (coordinate.getY() * 16)) * 5)));
                this->primaryMarkersP1Vector.push_back(this->primaryMissMarkerSprite);
            } else {
                this->primaryHitMarkerSprite.setPosition(sf::Vector2f(((128 + (coordinate.getX() * 16)) * 5), ((28 + (coordinate.getY() * 16)) * 5)));
                this->primaryMarkersP1Vector.push_back(this->primaryHitMarkerSprite);
            }
        } else {
            if (attack == SquareType::WATER) {
                this->secondaryMissMarkerSprite.setPosition(sf::Vector2f(((16 + (coordinate.getX() * 8)) * 5), ((44 + (coordinate.getY() * 8)) * 5)));
                this->secondaryMarkersP1Vector.push_back(this->secondaryMissMarkerSprite);
            } else {
                this->secondaryHitMarkerSprite.setPosition(sf::Vector2f(((16 + (coordinate.getX() * 8)) * 5), ((44 + (coordinate.getY() * 8)) * 5)));
                this->secondaryMarkersP1Vector.push_back(this->secondaryHitMarkerSprite);
            }
        }

    } else {
        if (State::player == State::Player::P1) {
            if (attack == SquareType::WATER) {
                this->primaryMissMarkerSprite.setPosition(sf::Vector2f(((128 + (coordinate.getX() * 16)) * 5), ((28 + (coordinate.getY() * 16)) * 5)));
                this->primaryMarkersP1Vector.push_back(this->primaryMissMarkerSprite);

                this->secondaryMissMarkerSprite.setPosition(sf::Vector2f(((16 + (coordinate.getX() * 8)) * 5), ((44 + (coordinate.getY() * 8)) * 5)));
                this->secondaryMarkersP2Vector.push_back(this->secondaryMissMarkerSprite);
            } else {
                this->primaryHitMarkerSprite.setPosition(sf::Vector2f(((128 + (coordinate.getX() * 16)) * 5), ((28 + (coordinate.getY() * 16)) * 5)));
                this->primaryMarkersP1Vector.push_back(this->primaryHitMarkerSprite);

                this->secondaryHitMarkerSprite.setPosition(sf::Vector2f(((16 + (coordinate.getX() * 8)) * 5), ((44 + (coordinate.getY() * 8)) * 5)));
                this->secondaryMarkersP2Vector.push_back(this->secondaryHitMarkerSprite);
            }
        } else {
            if (attack == SquareType::WATER) {
                this->primaryMissMarkerSprite.setPosition(sf::Vector2f(((128 + (coordinate.getX() * 16)) * 5), ((28 + (coordinate.getY() * 16)) * 5)));
                this->primaryMarkersP2Vector.push_back(this->primaryMissMarkerSprite);

                this->secondaryMissMarkerSprite.setPosition(sf::Vector2f(((16 + (coordinate.getX() * 8)) * 5), ((44 + (coordinate.getY() * 8)) * 5)));
                this->secondaryMarkersP1Vector.push_back(this->secondaryMissMarkerSprite);
            } else {
                this->primaryHitMarkerSprite.setPosition(sf::Vector2f(((128 + (coordinate.getX() * 16)) * 5), ((28 + (coordinate.getY() * 16)) * 5)));
                this->primaryMarkersP2Vector.push_back(this->primaryHitMarkerSprite);

                this->secondaryHitMarkerSprite.setPosition(sf::Vector2f(((16 + (coordinate.getX() * 8)) * 5), ((44 + (coordinate.getY() * 8)) * 5)));
                this->secondaryMarkersP1Vector.push_back(this->secondaryHitMarkerSprite);
            }
        }
    }
}

void Gameplay::resetGridMarkers() {
    this->primaryMarkersP1Vector.clear();
    this->primaryMarkersP2Vector.clear();
    this->secondaryMarkersP1Vector.clear();
    this->secondaryMarkersP2Vector.clear();
}

void Gameplay::updateSecondaryTarget(Coordinate coordinate) {
    this->secondaryTargetSprite.setPosition(sf::Vector2f(((16 + (coordinate.getX() * 8)) * 5), ((44 + (coordinate.getY() * 8)) * 5)));
}

void Gameplay::updateGrid(Coordinate &coordinate, sf::RenderWindow &gui) {
    if (State::gameMode == State::GameMode::SINGLE_PLAYER) {
        if (State::player == State::Player::P1) {
            SquareType attack = this->gridP2->attack(coordinate);
            if (attack == SquareType::WATER) {
                this->updateGridMarkers(attack, coordinate);
                this->render();
                sleepMS();
                State::player = State::Player::P2;
            } else if (attack == SquareType::SHIP) {
                this->updateGridMarkers(attack, coordinate);
                this->render();
                sleepMS();
                if (lost(*(this->gridP2))) {
                    this->resetGridMarkers();
                    State::player = State::Player::P2;
                    State::changeScreen(Screens::GAME_OVER);
                } else {
                    State::player = State::Player::P2;
                }
            }

        } else {
            SquareType attack = this->gridP1->attack(coordinate);
            if (attack == SquareType::WATER) {
                this->updateGridMarkers(attack, coordinate);
                this->updateSecondaryTarget(coordinate);
                State::player = State::Player::P1;
            } else if (attack == SquareType::SHIP) {
                this->updateGridMarkers(attack, coordinate);
                this->updateSecondaryTarget(coordinate);
                if (lost(*(this->gridP1))) {
                    this->resetGridMarkers();
                    State::player = State::Player::P1;
                    State::changeScreen(Screens::GAME_OVER);
                } else {
                    State::player = State::Player::P1;
                }
            }
        }


    } else {
        if (State::player == State::Player::P1) {
            SquareType attack = this->gridP2->attack(coordinate);
            if (attack == SquareType::WATER) {
                this->updateGridMarkers(attack, coordinate);
                this->render();
                this->updateSecondaryTarget(coordinate);
                sleepMS();
                State::player = State::Player::P2;
                State::changeScreen(Screens::INTERMEDIARY);
            } else if (attack == SquareType::SHIP) {
                this->updateGridMarkers(attack, coordinate);
                this->render();
                this->updateSecondaryTarget(coordinate);
                sleepMS();
                if (lost(*(this->gridP2))) {
                    this->resetGridMarkers();
                    State::player = State::Player::P2;
                    State::changeScreen(Screens::GAME_OVER);
                } else {
                    State::player = State::Player::P2;
                    State::changeScreen(Screens::INTERMEDIARY);
                }
            }

        } else {
            SquareType attack = this->gridP1->attack(coordinate);
            if (attack == SquareType::WATER) {
                this->updateGridMarkers(attack, coordinate);
                this->render();
                this->updateSecondaryTarget(coordinate);
                sleepMS();
                State::player = State::Player::P1;
                State::changeScreen(Screens::INTERMEDIARY);
            } else if (attack == SquareType::SHIP) {
                this->updateGridMarkers(attack, coordinate);
                this->render();
                this->updateSecondaryTarget(coordinate);
                if (lost(*(this->gridP1))) {
                    sleepMS();
                    this->resetGridMarkers();
                    State::player = State::Player::P1;
                    State::changeScreen(Screens::GAME_OVER);
                } else {
                    sleepMS();
                    State::player = State::Player::P1;
                    State::changeScreen(Screens::INTERMEDIARY);
                }
            }
        }
    }
}

void Gameplay::setFleetLayout(map<shipNames, tuple<Coordinate, bool>> &fleetLayout) {
    if (get<1>(fleetLayout[shipNames::BATTLESHIP]) == 1) {
        this->battleshipSprite.setPosition(sf::Vector2f((64 + (get<0>(fleetLayout[shipNames::BATTLESHIP]).getX() * 8)) * 5,
                                                        (44 + (get<0>(fleetLayout[shipNames::BATTLESHIP]).getY() * 8)) * 5));
        this->battleshipSprite.setRotation(90.f);
    } else {
        this->battleshipSprite.setPosition(sf::Vector2f((16 + (get<0>(fleetLayout[shipNames::BATTLESHIP]).getX() * 8)) * 5,
                                                        (44 + (get<0>(fleetLayout[shipNames::BATTLESHIP]).getY() * 8)) * 5));
        this->battleshipSprite.setRotation(0);
    }

    if (get<1>(fleetLayout[shipNames::AIRCRAFT_CARRIER]) == 1) {
        this->aircraftCarrierSprite.setPosition(sf::Vector2f((56 + (get<0>(fleetLayout[shipNames::AIRCRAFT_CARRIER]).getX() * 8)) * 5,
                                                             (44 + (get<0>(fleetLayout[shipNames::AIRCRAFT_CARRIER]).getY() * 8)) * 5));
        this->aircraftCarrierSprite.setRotation(90.f);
    } else {
        this->aircraftCarrierSprite.setPosition(sf::Vector2f((16 + (get<0>(fleetLayout[shipNames::AIRCRAFT_CARRIER]).getX() * 8)) * 5,
                                                             (44 + (get<0>(fleetLayout[shipNames::AIRCRAFT_CARRIER]).getY() * 8)) * 5));
        this->aircraftCarrierSprite.setRotation(0);
    }

    if (get<1>(fleetLayout[shipNames::DESTROYER]) == 1) {
        this->destroyerSprite.setPosition(sf::Vector2f((48 + (get<0>(fleetLayout[shipNames::DESTROYER]).getX() * 8)) * 5,
                                                       (44 + (get<0>(fleetLayout[shipNames::DESTROYER]).getY() * 8)) * 5));
        this->destroyerSprite.setRotation(90.f);
    } else {
        this->destroyerSprite.setPosition(sf::Vector2f((16 + (get<0>(fleetLayout[shipNames::DESTROYER]).getX() * 8)) * 5,
                                                       (44 + (get<0>(fleetLayout[shipNames::DESTROYER]).getY() * 8)) * 5));
        this->destroyerSprite.setRotation(0);
    }

    if (get<1>(fleetLayout[shipNames::SUBMARINE]) == 1) {
        this->submarineSprite.setPosition(sf::Vector2f((40 + (get<0>(fleetLayout[shipNames::SUBMARINE]).getX() * 8)) * 5,
                                                       (44 + (get<0>(fleetLayout[shipNames::SUBMARINE]).getY() * 8)) * 5));
        this->submarineSprite.setRotation(90.f);
    } else {
        this->submarineSprite.setPosition(sf::Vector2f((16 + (get<0>(fleetLayout[shipNames::SUBMARINE]).getX() * 8)) * 5,
                                                       (44 + (get<0>(fleetLayout[shipNames::SUBMARINE]).getY() * 8)) * 5));
        this->submarineSprite.setRotation(0);
    }

    if (get<1>(fleetLayout[shipNames::PATROL_BOAT]) == 1) {
        this->patrolBoatSprite.setPosition(sf::Vector2f((32 + (get<0>(fleetLayout[shipNames::PATROL_BOAT]).getX() * 8)) * 5,
                                                        (44 + (get<0>(fleetLayout[shipNames::PATROL_BOAT]).getY() * 8)) * 5));
        this->patrolBoatSprite.setRotation(90.f);
    } else {
        this->patrolBoatSprite.setPosition(sf::Vector2f((16 + (get<0>(fleetLayout[shipNames::PATROL_BOAT]).getX() * 8)) * 5,
                                                        (44 + (get<0>(fleetLayout[shipNames::PATROL_BOAT]).getY() * 8)) * 5));
        this->patrolBoatSprite.setRotation(0);
    }

    if (get<1>(fleetLayout[shipNames::ROW_BOAT]) == 1) {
        this->rowBoatSprite.setPosition(sf::Vector2f((24 + (get<0>(fleetLayout[shipNames::ROW_BOAT]).getX() * 8)) * 5,
                                                     (44 + (get<0>(fleetLayout[shipNames::ROW_BOAT]).getY() * 8)) * 5));
        this->rowBoatSprite.setRotation(90.0);
    } else {
        this->rowBoatSprite.setPosition(sf::Vector2f((16 + (get<0>(fleetLayout[shipNames::ROW_BOAT]).getX() * 8)) * 5,
                                                     (44 + (get<0>(fleetLayout[shipNames::ROW_BOAT]).getY() * 8)) * 5));
        this->rowBoatSprite.setRotation(0);
    }
}

void Gameplay::update() {
    sf::Vector2f mousePosition = State::getMousePosition();

    this->surrenderButton->updateButtonState(mousePosition);
    this->instructionsButton->updateButtonState(mousePosition);

    for (auto &target : this->targetVector) {
        target.updateTargetState(mousePosition);
    }

    if (State::gameMode == State::GameMode::SINGLE_PLAYER) {
        this->setFleetLayout(this->fleetLayoutP1);
    } else {
        if (State::player == State::Player::P1) {
            this->setFleetLayout(this->fleetLayoutP1);
        } else {
            this->setFleetLayout(this->fleetLayoutP2);
        }
    }

    if ((State::gameMode == State::GameMode::SINGLE_PLAYER) && (State::player == State::Player::P2)) {
        if (State::difficulty == State::Difficulty::EASY) {
            Coordinate attack = this->randomAttack();
            this->updateGrid(attack, *State::gui);
        } else {
            // TODO: Add hard algorithm
            Coordinate attack = this->randomAttack();
            this->updateGrid(attack, *State::gui);
        }
    }

    State::lockedFlag = false;
}

void Gameplay::poll() {
    sf::RenderWindow &gui = *State::gui;
    sf::Event &event = State::event;

    while (gui.pollEvent(event)) {
        switch (event.type) {

            case sf::Event::Closed:
                gui.close();
                break;

            case sf::Event::MouseButtonReleased:
                if ((event.mouseButton.button == sf::Mouse::Left) && (this->surrenderButton->getButtonState())) {
                    this->resetGridMarkers();
                    State::changeScreen(Screens::GAME_OVER);
                    break;
                } else if ((event.mouseButton.button == sf::Mouse::Left) && (this->instructionsButton->getButtonState())) {
                    State::changeScreen(Screens::INSTRUCTIONS);
                    break;
                } else if ((event.mouseButton.button == sf::Mouse::Left) && !State::lockedFlag) {
                    for (auto &target : this->targetVector) {
                        if (target.getTargetState()) {
                            State::lockedFlag = true;
                            Coordinate targetCoord = target.getTargetCoordinate();
                            this->updateGrid(targetCoord, gui);
                        }
                    }
                    break;
                } else {
                    break;
                }

            default:
                break;
        }
    }
}

void Gameplay::renderShipStatus(Grid &grid) {
    sf::RenderWindow &gui = *State::gui;
    map<shipNames, bool> shipStatus = grid.getShipStatus();

    if (shipStatus[shipNames::BATTLESHIP]) {
        gui.draw(this->battleshipSunkSprite);
    }

    if (shipStatus[shipNames::AIRCRAFT_CARRIER]) {
        gui.draw(this->aircraftCarrierSunkSprite);
    }

    if (shipStatus[shipNames::DESTROYER]) {
        gui.draw(this->destroyerSunkSprite);
    }

    if (shipStatus[shipNames::SUBMARINE]) {
        gui.draw(this->submarineSunkSprite);
    }

    if (shipStatus[shipNames::PATROL_BOAT]) {
        gui.draw(this->patrolBoatSunkSprite);
    }

    if (shipStatus[shipNames::ROW_BOAT]) {
        gui.draw(this->rowBoatSunkSprite);
    }
}

void Gameplay::render() {
    sf::RenderWindow &gui = *State::gui;
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

    surrenderButton->render(gui);
    instructionsButton->render(gui);

    gui.draw(this->battleshipSprite);
    gui.draw(this->aircraftCarrierSprite);
    gui.draw(this->destroyerSprite);
    gui.draw(this->submarineSprite);
    gui.draw(this->patrolBoatSprite);
    gui.draw(this->rowBoatSprite);

    if (State::gameMode == State::SINGLE_PLAYER) {
        for (auto &primaryMarker : this->primaryMarkersP1Vector) {
            gui.draw(primaryMarker);
        }
        for (auto &secondaryMarker : this->secondaryMarkersP1Vector) {
            gui.draw(secondaryMarker);
        }
    } else {
        if (State::player == State::Player::P1) {
            for (auto &primaryMarker : this->primaryMarkersP1Vector) {
                gui.draw(primaryMarker);
            }

            for (auto &secondaryMarker : this->secondaryMarkersP1Vector) {
                gui.draw(secondaryMarker);
            }
        } else {
            for (auto &primaryMarker : this->primaryMarkersP2Vector) {
                gui.draw(primaryMarker);
            }

            for (auto &secondaryMarker : this->secondaryMarkersP2Vector) {
                gui.draw(secondaryMarker);
            }
        }
    }

    if ((State::player == State::Player::P1) && !this->secondaryMarkersP1Vector.empty()) {
        gui.draw(this->secondaryTargetSprite);
    }

    if ((State::player == State::Player::P2) && !this->secondaryMarkersP2Vector.empty()) {
        gui.draw(this->secondaryTargetSprite);
    }

    if (State::gameMode == State::SINGLE_PLAYER) {
        this->renderShipStatus(*(this->gridP2));
    } else {
        if (State::player == State::Player::P1) {
            this->renderShipStatus(*(screen::Gameplay::gridP2));
        } else {
            this->renderShipStatus(*(screen::Gameplay::gridP1));
        }
    }

    for (auto &target : this->targetVector) {
        target.render(gui);
    }

    if (State::getCurrentScreen() == Screens::GAMEPLAY) {
        gui.display();
    }
}

void Gameplay::run() {
    this->update();
    this->poll();
    this->render();
}

void screen::Gameplay::sleepMS() {
#ifdef _WIN32
    Sleep(sleepTimeMS);
#else
    usleep(sleepTimeMS * 1000);
#endif// _WIN32
}

Gameplay &screen::Gameplay::getInstance() {
    if (instance == nullptr) {
        instance = new Gameplay;
    }
    return *instance;
}
