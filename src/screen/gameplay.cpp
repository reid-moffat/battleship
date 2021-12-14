/**
 * File: gameplay.cpp
 * Description: Front-end class that defines the behaviour of the Gameplay screen
 */

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "../../include/screen/gameplay.h"

using entity::SquareType;
using screen::Gameplay;
using std::get;

// Static fields are required to be initialized
__attribute__((unused)) Grid *Gameplay::gridP1 = new Grid();
__attribute__((unused)) Grid *Gameplay::gridP2 = new Grid();

Gameplay::Gameplay() : ScreenTemplate() {
    State::loadTexture(this->gameplayDefaultBackgroundTexture, "gameplay/GameplayBackground.png");
    State::loadTexture(this->gameplayP1BackgroundTexture, "gameplay/GameplayP1Background.png");
    State::loadTexture(this->gameplayP2BackgroundTexture, "gameplay/GameplayP2Background.png");

    State::loadTexture(this->idleSurrenderButtonTexture, "gameplay/IdleSurrenderButton.png");
    State::loadTexture(this->activeSurrenderButtonTexture, "gameplay/ActiveSurrenderButton.png");
    State::loadTexture(this->idleInstructionsButtonTexture, "gameplay/IdleInstructionsButton.png");
    State::loadTexture(this->activeInstructionsButtonTexture, "gameplay/ActiveInstructionsButton.png");

    State::loadTexture(this->battleshipTexture, "gameplay/BattleShip.png");
    State::loadTexture(this->aircraftCarrierTexture, "gameplay/AircraftCarrier.png");
    State::loadTexture(this->destroyerTexture, "gameplay/Destroyer.png");
    State::loadTexture(this->submarineTexture, "gameplay/Submarine.png");
    State::loadTexture(this->patrolBoatTexture, "gameplay/PatrolBoat.png");
    State::loadTexture(this->rowBoatTexture, "gameplay/RowBoat.png");

    State::loadTexture(this->battleshipSunkTexture, "gameplay/BattleShipSunk.png");
    State::loadTexture(this->aircraftCarrierSunkTexture, "gameplay/AircraftCarrierSunk.png");
    State::loadTexture(this->destroyerSunkTexture, "gameplay/DestroyerSunk.png");
    State::loadTexture(this->submarineSunkTexture, "gameplay/SubmarineSunk.png");
    State::loadTexture(this->patrolBoatSunkTexture, "gameplay/PatrolBoatSunk.png");
    State::loadTexture(this->rowBoatSunkTexture, "gameplay/RowBoatSunk.png");

    State::loadTexture(this->primaryHitMarkerTexture, "gameplay/PrimaryHitMarker.png");
    State::loadTexture(this->primaryMissMarkerTexture, "gameplay/PrimaryMissMarker.png");
    State::loadTexture(this->secondaryHitMarkerTexture, "gameplay/SecondaryHitMarker.png");
    State::loadTexture(this->secondaryMissMarkerTexture, "gameplay/SecondaryMissMarker.png");

    State::loadTexture(this->idlePrimaryTargetTexture, "gameplay/idlePrimaryTarget.png");
    State::loadTexture(this->activePrimaryTargetTexture, "gameplay/ActivePrimaryTarget.png");
    State::loadTexture(this->secondaryTargetTexture, "gameplay/SecondaryTarget.png");

    State::setSprite(sf::Vector2f(0, 0), sf::Vector2f(5, 5), this->gameplayDefaultBackgroundTexture, this->backgroundDefaultSprite);
    State::setSprite(sf::Vector2f(0, 0), sf::Vector2f(5, 5), this->gameplayP1BackgroundTexture, this->backgroundP1Sprite);
    State::setSprite(sf::Vector2f(0, 0), sf::Vector2f(5, 5), this->gameplayP2BackgroundTexture, this->backgroundP2Sprite);

    State::setSprite(sf::Vector2f(330 * 5, 113 * 5), sf::Vector2f(5, 5), this->battleshipSunkTexture, this->battleshipSunkSprite);
    State::setSprite(sf::Vector2f(348 * 5, 117 * 5), sf::Vector2f(5, 5), this->aircraftCarrierSunkTexture, this->aircraftCarrierSunkSprite);
    State::setSprite(sf::Vector2f(348 * 5, 75 * 5), sf::Vector2f(5, 5), this->destroyerSunkTexture, this->destroyerSunkSprite);
    State::setSprite(sf::Vector2f(330 * 5, 79 * 5), sf::Vector2f(5, 5), this->submarineSunkTexture, this->submarineSunkSprite);
    State::setSprite(sf::Vector2f(330 * 5, 53 * 5), sf::Vector2f(5, 5), this->patrolBoatSunkTexture, this->patrolBoatSunkSprite);
    State::setSprite(sf::Vector2f(348 * 5, 57 * 5), sf::Vector2f(5, 5), this->rowBoatSunkTexture, this->rowBoatSunkSprite);

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

Gameplay::Gameplay(const Gameplay &source) {
    this->gameplayDefaultBackgroundTexture = source.gameplayDefaultBackgroundTexture;
    this->gameplayP1BackgroundTexture = source.gameplayP1BackgroundTexture;
    this->gameplayP2BackgroundTexture = source.gameplayP2BackgroundTexture;

    this->idleSurrenderButtonTexture = source.idleSurrenderButtonTexture;
    this->activeSurrenderButtonTexture = source.activeSurrenderButtonTexture;
    this->idleInstructionsButtonTexture = source.idleInstructionsButtonTexture;
    this->activeInstructionsButtonTexture = source.activeInstructionsButtonTexture;

    this->battleshipTexture = source.battleshipTexture;
    this->aircraftCarrierTexture = source.aircraftCarrierTexture;
    this->destroyerTexture = source.destroyerTexture;
    this->submarineTexture = source.submarineTexture;
    this->patrolBoatTexture = source.patrolBoatTexture;
    this->rowBoatTexture = source.rowBoatTexture;

    this->battleshipSunkTexture = source.battleshipSunkTexture;
    this->aircraftCarrierSunkTexture = source.aircraftCarrierSunkTexture;
    this->destroyerSunkTexture = source.destroyerSunkTexture;
    this->submarineSunkTexture = source.submarineSunkTexture;
    this->patrolBoatSunkTexture = source.patrolBoatSunkTexture;
    this->rowBoatSunkTexture = source.rowBoatSunkTexture;

    this->primaryHitMarkerTexture = source.primaryHitMarkerTexture;
    this->primaryMissMarkerTexture = source.primaryMissMarkerTexture;
    this->secondaryHitMarkerTexture = source.secondaryHitMarkerTexture;
    this->secondaryMissMarkerTexture = source.secondaryMissMarkerTexture;

    this->idlePrimaryTargetTexture = source.idlePrimaryTargetTexture;
    this->activePrimaryTargetTexture = source.activePrimaryTargetTexture;
    this->secondaryTargetTexture = source.secondaryTargetTexture;

    this->backgroundDefaultSprite = source.backgroundDefaultSprite;
    this->backgroundP1Sprite = source.backgroundP1Sprite;
    this->backgroundP2Sprite = source.backgroundP2Sprite;

    this->battleshipSprite = source.battleshipSprite;
    this->aircraftCarrierSprite = source.aircraftCarrierSprite;
    this->destroyerSprite = source.destroyerSprite;
    this->submarineSprite = source.submarineSprite;
    this->patrolBoatSprite = source.patrolBoatSprite;
    this->rowBoatSprite = source.rowBoatSprite;

    this->battleshipSunkSprite = source.battleshipSunkSprite;
    this->aircraftCarrierSunkSprite = source.aircraftCarrierSunkSprite;
    this->destroyerSunkSprite = source.destroyerSunkSprite;
    this->submarineSunkSprite = source.submarineSunkSprite;
    this->patrolBoatSunkSprite = source.patrolBoatSunkSprite;
    this->rowBoatSunkSprite = source.rowBoatSunkSprite;

    this->primaryHitMarkerSprite = source.primaryHitMarkerSprite;
    this->primaryMissMarkerSprite = source.primaryMissMarkerSprite;
    this->secondaryHitMarkerSprite = source.secondaryHitMarkerSprite;
    this->secondaryMissMarkerSprite = source.secondaryMissMarkerSprite;

    this->secondaryTargetSprite = source.secondaryTargetSprite;

    this->targetVector = source.targetVector;

    this->primaryMarkersP1Vector = source.primaryMarkersP1Vector;
    this->primaryMarkersP2Vector = source.primaryMarkersP2Vector;
    this->secondaryMarkersP1Vector = source.secondaryMarkersP1Vector;
    this->secondaryMarkersP2Vector = source.secondaryMarkersP2Vector;

    this->fleetLayoutP1 = source.fleetLayoutP1;
    this->fleetLayoutP2 = source.fleetLayoutP2;

    this->coordinateSet = source.coordinateSet;
    this->mousePosition = source.mousePosition;
    this->event = source.event;

    this->surrenderButton = new Button(*(source.surrenderButton));
    this->instructionsButton = new Button(*(source.instructionsButton));

    this->gridP1 = new Grid(*(source.gridP1));
    this->gridP2 = new Grid(*(source.gridP2));
}

Gameplay::~Gameplay() {
    delete this->surrenderButton;
    this->surrenderButton = nullptr;

    delete this->instructionsButton;
    this->instructionsButton = nullptr;

    delete this->instructionsButton;
    this->instructionsButton = nullptr;

    delete this->gridP1;
    this->gridP1 = nullptr;

    delete this->gridP2;
    this->gridP2 = nullptr;
}

screen::Gameplay &Gameplay::operator=(const Gameplay &source) {
    if (this == &source) {
        return *this;
    } else {
        this->gameplayDefaultBackgroundTexture = source.gameplayDefaultBackgroundTexture;
        this->gameplayP1BackgroundTexture = source.gameplayP1BackgroundTexture;
        this->gameplayP2BackgroundTexture = source.gameplayP2BackgroundTexture;

        this->idleSurrenderButtonTexture = source.idleSurrenderButtonTexture;
        this->activeSurrenderButtonTexture = source.activeSurrenderButtonTexture;
        this->idleInstructionsButtonTexture = source.idleInstructionsButtonTexture;
        this->activeInstructionsButtonTexture = source.activeInstructionsButtonTexture;

        this->battleshipTexture = source.battleshipTexture;
        this->aircraftCarrierTexture = source.aircraftCarrierTexture;
        this->destroyerTexture = source.destroyerTexture;
        this->submarineTexture = source.submarineTexture;
        this->patrolBoatTexture = source.patrolBoatTexture;
        this->rowBoatTexture = source.rowBoatTexture;

        this->battleshipSunkTexture = source.battleshipSunkTexture;
        this->aircraftCarrierSunkTexture = source.aircraftCarrierSunkTexture;
        this->destroyerSunkTexture = source.destroyerSunkTexture;
        this->submarineSunkTexture = source.submarineSunkTexture;
        this->patrolBoatSunkTexture = source.patrolBoatSunkTexture;
        this->rowBoatSunkTexture = source.rowBoatSunkTexture;

        this->primaryHitMarkerTexture = source.primaryHitMarkerTexture;
        this->primaryMissMarkerTexture = source.primaryMissMarkerTexture;
        this->secondaryHitMarkerTexture = source.secondaryHitMarkerTexture;
        this->secondaryMissMarkerTexture = source.secondaryMissMarkerTexture;

        this->idlePrimaryTargetTexture = source.idlePrimaryTargetTexture;
        this->activePrimaryTargetTexture = source.activePrimaryTargetTexture;
        this->secondaryTargetTexture = source.secondaryTargetTexture;

        this->backgroundDefaultSprite = source.backgroundDefaultSprite;
        this->backgroundP1Sprite = source.backgroundP1Sprite;
        this->backgroundP2Sprite = source.backgroundP2Sprite;

        this->battleshipSprite = source.battleshipSprite;
        this->aircraftCarrierSprite = source.aircraftCarrierSprite;
        this->destroyerSprite = source.destroyerSprite;
        this->submarineSprite = source.submarineSprite;
        this->patrolBoatSprite = source.patrolBoatSprite;
        this->rowBoatSprite = source.rowBoatSprite;

        this->battleshipSunkSprite = source.battleshipSunkSprite;
        this->aircraftCarrierSunkSprite = source.aircraftCarrierSunkSprite;
        this->destroyerSunkSprite = source.destroyerSunkSprite;
        this->submarineSunkSprite = source.submarineSunkSprite;
        this->patrolBoatSunkSprite = source.patrolBoatSunkSprite;
        this->rowBoatSunkSprite = source.rowBoatSunkSprite;

        this->primaryHitMarkerSprite = source.primaryHitMarkerSprite;
        this->primaryMissMarkerSprite = source.primaryMissMarkerSprite;
        this->secondaryHitMarkerSprite = source.secondaryHitMarkerSprite;
        this->secondaryMissMarkerSprite = source.secondaryMissMarkerSprite;

        this->secondaryTargetSprite = source.secondaryTargetSprite;

        this->targetVector = source.targetVector;

        this->primaryMarkersP1Vector = source.primaryMarkersP1Vector;
        this->primaryMarkersP2Vector = source.primaryMarkersP2Vector;
        this->secondaryMarkersP1Vector = source.secondaryMarkersP1Vector;
        this->secondaryMarkersP2Vector = source.secondaryMarkersP2Vector;

        this->fleetLayoutP1 = source.fleetLayoutP1;
        this->fleetLayoutP2 = source.fleetLayoutP2;

        this->coordinateSet = source.coordinateSet;
        this->mousePosition = source.mousePosition;
        this->event = source.event;

        this->surrenderButton = source.surrenderButton;
        this->instructionsButton = source.instructionsButton;

        this->gridP1 = source.gridP2;
        this->gridP2 = source.gridP1;

        return *this;
    }
}

void Gameplay::setP1Grid(const map<shipsNames, tuple<Coordinate, bool>> &ships) {
    Gameplay::gridP1 = new Grid(ships);
}

void Gameplay::setP2Grid(const map<shipsNames, tuple<Coordinate, bool>> &ships) {
    Gameplay::gridP2 = new Grid(ships);
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
    int randGen = rand() % this->coordinateSet.size();
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
            Target target(coordinate, sf::Vector2f(((128 + (x * 16)) * 5), ((28 + (y * 16)) * 5)), sf::Vector2f(5, 5),
                          this->idlePrimaryTargetTexture, this->activePrimaryTargetTexture);
            targetVector.push_back(target);
        }
    }
}

bool Gameplay::lost(Grid &grid) {
    map<shipsNames, bool> shipStatus = grid.getShipStatus();
    for (auto itr = shipStatus.begin(); itr != shipStatus.end(); itr++) {
        if (itr->second == false) {
            return false;
        }
    }
    return true;
}

void Gameplay::updateGridMarkers(SquareType attack, Coordinate coordinate) {
    if (State::gameMode == State::GameMode::SinglePlayer) {
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

void Gameplay::updateGrid(Coordinate coordinate, sf::RenderWindow &gui) {
    if (State::gameMode == State::GameMode::SinglePlayer) {
        if (State::player == State::Player::P1) {
            SquareType attack = this->gridP2->attack(coordinate);
            if (attack == SquareType::WATER) {
                this->updateGridMarkers(attack, coordinate);
                this->render(gui);
                sleepMS();
                State::player = State::Player::P2;
            } else if (attack == SquareType::SHIP) {
                this->updateGridMarkers(attack, coordinate);
                this->render(gui);
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
                this->render(gui);
                this->updateSecondaryTarget(coordinate);
                sleepMS();
                State::player = State::Player::P2;
                State::changeScreen(Screens::INTERMEDIARY);
            } else if (attack == SquareType::SHIP) {
                this->updateGridMarkers(attack, coordinate);
                this->render(gui);
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
                this->render(gui);
                this->updateSecondaryTarget(coordinate);
                sleepMS();
                State::player = State::Player::P1;
                State::changeScreen(Screens::INTERMEDIARY);
            } else if (attack == SquareType::SHIP) {
                this->updateGridMarkers(attack, coordinate);
                this->render(gui);
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

void Gameplay::setFleetLayout(map<shipsNames, tuple<Coordinate, bool>> &fleetLayout) {
    if (get<1>(fleetLayout[shipsNames::BATTLESHIP]) == 1) {
        this->battleshipSprite.setPosition(sf::Vector2f((64 + (get<0>(fleetLayout[shipsNames::BATTLESHIP]).getX() * 8)) * 5,
                                                        (44 + (get<0>(fleetLayout[shipsNames::BATTLESHIP]).getY() * 8)) * 5));
        this->battleshipSprite.setRotation(90.f);
    } else {
        this->battleshipSprite.setPosition(sf::Vector2f((16 + (get<0>(fleetLayout[shipsNames::BATTLESHIP]).getX() * 8)) * 5,
                                                        (44 + (get<0>(fleetLayout[shipsNames::BATTLESHIP]).getY() * 8)) * 5));
        this->battleshipSprite.setRotation(0);
    }

    if (get<1>(fleetLayout[shipsNames::AIRCRAFT_CARRIER]) == 1) {
        this->aircraftCarrierSprite.setPosition(sf::Vector2f((56 + (get<0>(fleetLayout[shipsNames::AIRCRAFT_CARRIER]).getX() * 8)) * 5,
                                                             (44 + (get<0>(fleetLayout[shipsNames::AIRCRAFT_CARRIER]).getY() * 8)) * 5));
        this->aircraftCarrierSprite.setRotation(90.f);
    } else {
        this->aircraftCarrierSprite.setPosition(sf::Vector2f((16 + (get<0>(fleetLayout[shipsNames::AIRCRAFT_CARRIER]).getX() * 8)) * 5,
                                                             (44 + (get<0>(fleetLayout[shipsNames::AIRCRAFT_CARRIER]).getY() * 8)) * 5));
        this->aircraftCarrierSprite.setRotation(0);
    }

    if (get<1>(fleetLayout[shipsNames::DESTROYER]) == 1) {
        this->destroyerSprite.setPosition(sf::Vector2f((48 + (get<0>(fleetLayout[shipsNames::DESTROYER]).getX() * 8)) * 5,
                                                       (44 + (get<0>(fleetLayout[shipsNames::DESTROYER]).getY() * 8)) * 5));
        this->destroyerSprite.setRotation(90.f);
    } else {
        this->destroyerSprite.setPosition(sf::Vector2f((16 + (get<0>(fleetLayout[shipsNames::DESTROYER]).getX() * 8)) * 5,
                                                       (44 + (get<0>(fleetLayout[shipsNames::DESTROYER]).getY() * 8)) * 5));
        this->destroyerSprite.setRotation(0);
    }

    if (get<1>(fleetLayout[shipsNames::SUBMARINE]) == 1) {
        this->submarineSprite.setPosition(sf::Vector2f((40 + (get<0>(fleetLayout[shipsNames::SUBMARINE]).getX() * 8)) * 5,
                                                       (44 + (get<0>(fleetLayout[shipsNames::SUBMARINE]).getY() * 8)) * 5));
        this->submarineSprite.setRotation(90.f);
    } else {
        this->submarineSprite.setPosition(sf::Vector2f((16 + (get<0>(fleetLayout[shipsNames::SUBMARINE]).getX() * 8)) * 5,
                                                       (44 + (get<0>(fleetLayout[shipsNames::SUBMARINE]).getY() * 8)) * 5));
        this->submarineSprite.setRotation(0);
    }

    if (get<1>(fleetLayout[shipsNames::PATROL_BOAT]) == 1) {
        this->patrolBoatSprite.setPosition(sf::Vector2f((32 + (get<0>(fleetLayout[shipsNames::PATROL_BOAT]).getX() * 8)) * 5,
                                                        (44 + (get<0>(fleetLayout[shipsNames::PATROL_BOAT]).getY() * 8)) * 5));
        this->patrolBoatSprite.setRotation(90.f);
    } else {
        this->patrolBoatSprite.setPosition(sf::Vector2f((16 + (get<0>(fleetLayout[shipsNames::PATROL_BOAT]).getX() * 8)) * 5,
                                                        (44 + (get<0>(fleetLayout[shipsNames::PATROL_BOAT]).getY() * 8)) * 5));
        this->patrolBoatSprite.setRotation(0);
    }

    if (get<1>(fleetLayout[shipsNames::ROW_BOAT]) == 1) {
        this->rowBoatSprite.setPosition(sf::Vector2f((24 + (get<0>(fleetLayout[shipsNames::ROW_BOAT]).getX() * 8)) * 5,
                                                     (44 + (get<0>(fleetLayout[shipsNames::ROW_BOAT]).getY() * 8)) * 5));
        this->rowBoatSprite.setRotation(90.0);
    } else {
        this->rowBoatSprite.setPosition(sf::Vector2f((16 + (get<0>(fleetLayout[shipsNames::ROW_BOAT]).getX() * 8)) * 5,
                                                     (44 + (get<0>(fleetLayout[shipsNames::ROW_BOAT]).getY() * 8)) * 5));
        this->rowBoatSprite.setRotation(0);
    }
}

void Gameplay::update(sf::RenderWindow &gui, sf::Vector2f mousePos) {
    State::updateMousePosition(gui, mousePos);

    this->surrenderButton->updateButtonState(mousePos);
    this->instructionsButton->updateButtonState(mousePos);

    for (auto &target : this->targetVector) {
        target.updateTargetState(mousePos);
    }

    if (State::gameMode == State::GameMode::SinglePlayer) {
        this->fleetLayoutP1 = this->gridP1->getShips();
        this->setFleetLayout(this->fleetLayoutP1);
    } else {
        if (State::player == State::Player::P1) {
            this->fleetLayoutP1 = this->gridP1->getShips();
            this->setFleetLayout(this->fleetLayoutP1);
        } else {
            this->setFleetLayout(this->fleetLayoutP2);
            this->fleetLayoutP2 = this->gridP2->getShips();
        }
    }

    if ((State::gameMode == State::GameMode::SinglePlayer) && (State::player == State::Player::P2)) {
        if (State::difficulty == State::Difficulty::EASY) {
            this->updateGrid(this->randomAttack(), gui);
        } else {
            this->updateGrid(this->randomAttack(), gui);
        }
    }

    State::lockedFlag = false;
}

void Gameplay::poll(sf::RenderWindow &gui) {
    while (gui.pollEvent(this->event)) {
        switch (this->event.type) {

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
                } else if ((event.mouseButton.button == sf::Mouse::Left) && (State::lockedFlag == false)) {
                    for (auto &target : this->targetVector) {
                        if (target.getTargetState() == true) {
                            State::lockedFlag = true;
                            this->updateGrid(target.getTargetCoordinate(), gui);
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

void Gameplay::renderShipStatus(Grid &grid, sf::RenderWindow &gui) {
    map<shipsNames, bool> shipStatus = grid.getShipStatus();

    if (shipStatus[shipsNames::BATTLESHIP] == true) {
        gui.draw(this->battleshipSunkSprite);
    }

    if (shipStatus[shipsNames::AIRCRAFT_CARRIER] == true) {
        gui.draw(this->aircraftCarrierSunkSprite);
    }

    if (shipStatus[shipsNames::DESTROYER] == true) {
        gui.draw(this->destroyerSunkSprite);
    }

    if (shipStatus[shipsNames::SUBMARINE] == true) {
        gui.draw(this->submarineSunkSprite);
    }

    if (shipStatus[shipsNames::PATROL_BOAT] == true) {
        gui.draw(this->patrolBoatSunkSprite);
    }

    if (shipStatus[shipsNames::ROW_BOAT] == true) {
        gui.draw(this->rowBoatSunkSprite);
    }
}

void Gameplay::render(sf::RenderWindow &gui) {
    gui.clear();

    if (State::gameMode == State::SinglePlayer) {
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

    if (State::gameMode == State::SinglePlayer) {
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

    if ((State::player == State::Player::P1) && (this->secondaryMarkersP1Vector.size() > 0)) {
        gui.draw(this->secondaryTargetSprite);
    }

    if ((State::player == State::Player::P2) && (this->secondaryMarkersP2Vector.size() > 0)) {
        gui.draw(this->secondaryTargetSprite);
    }

    if (State::gameMode == State::SinglePlayer) {
        this->renderShipStatus(*(this->gridP2), gui);
    } else {
        if (State::player == State::Player::P1) {
            this->renderShipStatus(*(this->gridP2), gui);
        } else {
            this->renderShipStatus(*(this->gridP1), gui);
        }
    }

    for (auto &target : this->targetVector) {
        target.render(gui);
    }

    if (State::getCurrentScreen() == Screens::GAMEPLAY) {
        gui.display();
    }
}

void Gameplay::run(sf::RenderWindow &gui) {
    this->update(gui, this->mousePosition);
    this->poll(gui);
    this->render(gui);
}

void screen::Gameplay::sleepMS() {
#ifdef _WIN32
    Sleep(500);
#else
    usleep(500000);
#endif// _WIN32
}