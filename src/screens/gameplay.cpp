/**
 * Stores a player's 10-by-10 grid and their ships
 */

#ifdef _WIN32
#include <Windows.h>
#include <memory>
#else
#include <unistd.h>
#endif

#include "../helpers/helperFunctions.hpp"
#include "gameplay.hpp"

using entity::SquareType;
using screen::Gameplay;
using std::get;

std::unique_ptr<Gameplay> Gameplay::instance = nullptr;

Gameplay::Gameplay() : ScreenTemplate() {
    // Data required for all the SFML objects on this screen
    const vector<string> texturePaths = {
            "GameplayBackground.png",
            "GameplayP1Background.png",
            "GameplayP2Background.png",

            "Battleship.png",
            "AircraftCarrier.png",
            "Destroyer.png",
            "Submarine.png",
            "PatrolBoat.png",
            "RowBoat.png",

            "BattleshipSunk.png",
            "AircraftCarrierSunk.png",
            "DestroyerSunk.png",
            "SubmarineSunk.png",
            "PatrolBoatSunk.png",
            "RowBoatSunk.png",

            "PrimaryHitMarker.png",
            "PrimaryMissMarker.png",
            "SecondaryHitMarker.png",
            "SecondaryMissMarker.png",
            "SecondaryTarget.png",

            "IdleSurrenderButton.png",
            "ActiveSurrenderButton.png",
            "IdleInstructionsButton.png",
            "ActiveInstructionsButton.png",
    };
    const vector<sprite> sprites = {
            {sf::Vector2f(0, 0), sf::Vector2f(5, 5), BackgroundDefaultTexture},
            {sf::Vector2f(0, 0), sf::Vector2f(5, 5), BackgroundP1Texture},
            {sf::Vector2f(0, 0), sf::Vector2f(5, 5), BackgroundP2Texture},

            {sf::Vector2f(0, 0), sf::Vector2f(5, 5), BattleshipTexture},
            {sf::Vector2f(0, 0), sf::Vector2f(5, 5), AircraftCarrierTexture},
            {sf::Vector2f(0, 0), sf::Vector2f(5, 5), DestroyerTexture},
            {sf::Vector2f(0, 0), sf::Vector2f(5, 5), SubmarineTexture},
            {sf::Vector2f(0, 0), sf::Vector2f(5, 5), PatrolBoatTexture},
            {sf::Vector2f(0, 0), sf::Vector2f(5, 5), RowBoatTexture},

            {sf::Vector2f(330 * 5, 113 * 5), sf::Vector2f(5, 5), BattleshipSunkTexture},
            {sf::Vector2f(348 * 5, 117 * 5), sf::Vector2f(5, 5), AircraftCarrierSunkTexture},
            {sf::Vector2f(348 * 5, 75 * 5), sf::Vector2f(5, 5), DestroyerSunkTexture},
            {sf::Vector2f(330 * 5, 79 * 5), sf::Vector2f(5, 5), SubmarineSunkTexture},
            {sf::Vector2f(330 * 5, 53 * 5), sf::Vector2f(5, 5), PatrolBoatSunkTexture},
            {sf::Vector2f(348 * 5, 57 * 5), sf::Vector2f(5, 5), RowBoatSunkTexture},

            {sf::Vector2f(0, 0), sf::Vector2f(5, 5), PrimaryHitMarkerTexture},
            {sf::Vector2f(0, 0), sf::Vector2f(5, 5), PrimaryMissMarkerTexture},
            {sf::Vector2f(0, 0), sf::Vector2f(5, 5), SecondaryHitMarkerTexture},
            {sf::Vector2f(0, 0), sf::Vector2f(5, 5), SecondaryMissMarkerTexture},
            {sf::Vector2f(0, 0), sf::Vector2f(5, 5), SecondaryTargetTexture},
    };
    const vector<button> buttons = {{sf::Vector2f(320 * 5, 12 * 5), sf::Vector2f(5, 5), IdleSurrenderButtonTexture, ActiveSurrenderButtonTexture},
                                    {sf::Vector2f(352 * 5, 12 * 5), sf::Vector2f(5, 5), IdleInstructionsButtonTexture, ActiveInstructionsButtonTexture}};

    // Initialize SFML objects
    this->resources = ScreenResourceManager("gameplay", texturePaths, sprites, buttons);


    // Initialize other required objects
    gridP1 = std::make_unique<Grid>();
    gridP2 = std::make_unique<Grid>();

    fleetLayoutP1 = std::make_unique<shipOrientations>();
    fleetLayoutP2 = std::make_unique<shipOrientations>();

    Target::initializeTextures("idlePrimaryTarget.png", "ActivePrimaryTarget.png");

    // Initializes the target locations
    for (int y = 0; y < 10; ++y) {
        for (int x = 0; x < 10; ++x) {
            Coordinate coordinate(x, y);
            Target target(coordinate, sf::Vector2f((float) (128 + (x * 16)) * 5, (float) (28 + (y * 16)) * 5), sf::Vector2f(5, 5));
            this->targetVector.push_back(target);
        }
    }

    // Initialize the set of possible coordinates the environment can attack
    for (int y = 0; y < 10; ++y) {
        for (int x = 0; x < 10; ++x) {
            Coordinate coordinate(x, y);
            this->coordinateSet.insert(coordinate);
        }
    }
}

Gameplay &screen::Gameplay::getInstance() {
    if (instance == nullptr) {
        instance.reset(new Gameplay);
    }
    return *instance;
}

void Gameplay::setP1Grid(const shipOrientations &ships) {
    gridP1 = std::make_unique<Grid>(ships);
    fleetLayoutP1.reset(&gridP1->getShips());
}

void Gameplay::setP2Grid(const shipOrientations &ships) {
    gridP2 = std::make_unique<Grid>(ships);
    fleetLayoutP2.reset(&gridP2->getShips());
}

Coordinate Gameplay::randomAttack() {
    // Generate a random index and get to the coordinate at that position
    const int randGen = randomInt(0, (int) this->coordinateSet.size() - 1);
    auto itr = this->coordinateSet.begin();
    advance(itr, randGen);

    // Remove the coordinate from the set and return it
    this->coordinateSet.erase(itr);
    return *itr;
}

bool Gameplay::lost(Grid &grid) {
    map<shipNames, bool> shipStatus = grid.getShipStatus();
    return std::all_of(shipStatus.cbegin(), shipStatus.cend(), [](const auto &ship) { return ship.second; });
}

void Gameplay::updateGridMarkers(SquareType attack, Coordinate coordinate) {
    if (State::gameMode == State::GameMode::SINGLE_PLAYER) {
        if (State::player == State::Player::P1) {
            if (attack == SquareType::Water) {
                resources.getSprite(PrimaryMissMarker)
                        .setPosition(sf::Vector2f((float) ((128 + (coordinate.getX() * 16)) * 5), (float) ((28 + (coordinate.getY() * 16)) * 5)));
                this->primaryMarkersP1Vector.push_back(resources.getSprite(PrimaryMissMarker));
            } else {
                resources.getSprite(PrimaryHitMarker)
                        .setPosition(sf::Vector2f((float) ((128 + (coordinate.getX() * 16)) * 5), (float) ((28 + (coordinate.getY() * 16)) * 5)));
                this->primaryMarkersP1Vector.push_back(resources.getSprite(PrimaryHitMarker));
            }
        } else {
            if (attack == SquareType::Water) {
                resources.getSprite(SecondaryMissMarker)
                        .setPosition(sf::Vector2f((float) ((16 + (coordinate.getX() * 8)) * 5), (float) ((44 + (coordinate.getY() * 8)) * 5)));
                this->secondaryMarkersP1Vector.push_back(resources.getSprite(SecondaryMissMarker));
            } else {
                resources.getSprite(SecondaryHitMarker)
                        .setPosition(sf::Vector2f((float) ((16 + (coordinate.getX() * 8)) * 5), (float) ((44 + (coordinate.getY() * 8)) * 5)));
                this->secondaryMarkersP1Vector.push_back(resources.getSprite(SecondaryHitMarker));
            }
        }
    } else {
        if (State::player == State::Player::P1) {
            if (attack == SquareType::Water) {
                resources.getSprite(PrimaryMissMarker)
                        .setPosition(sf::Vector2f((float) ((128 + (coordinate.getX() * 16)) * 5), (float) ((28 + (coordinate.getY() * 16)) * 5)));
                this->primaryMarkersP1Vector.push_back(resources.getSprite(PrimaryMissMarker));

                resources.getSprite(SecondaryMissMarker)
                        .setPosition(sf::Vector2f((float) ((16 + (coordinate.getX() * 8)) * 5), (float) ((44 + (coordinate.getY() * 8)) * 5)));
                this->secondaryMarkersP2Vector.push_back(resources.getSprite(SecondaryMissMarker));
            } else {
                resources.getSprite(PrimaryHitMarker)
                        .setPosition(sf::Vector2f((float) ((128 + (coordinate.getX() * 16)) * 5), (float) ((28 + (coordinate.getY() * 16)) * 5)));
                this->primaryMarkersP1Vector.push_back(resources.getSprite(PrimaryHitMarker));

                resources.getSprite(SecondaryHitMarker)
                        .setPosition(sf::Vector2f((float) ((16 + (coordinate.getX() * 8)) * 5), (float) ((44 + (coordinate.getY() * 8)) * 5)));
                this->secondaryMarkersP2Vector.push_back(resources.getSprite(SecondaryHitMarker));
            }
        } else {
            if (attack == SquareType::Water) {
                resources.getSprite(PrimaryMissMarker).
                        setPosition(sf::Vector2f((float) ((128 + (coordinate.getX() * 16)) * 5), (float) ((28 + (coordinate.getY() * 16)) * 5)));
                this->primaryMarkersP2Vector.push_back(resources.getSprite(PrimaryMissMarker));

                resources.getSprite(SecondaryMissMarker)
                        .setPosition(sf::Vector2f((float) ((16 + (coordinate.getX() * 8)) * 5), (float) ((44 + (coordinate.getY() * 8)) * 5)));
                this->secondaryMarkersP1Vector.push_back(resources.getSprite(SecondaryMissMarker));
            } else {
                resources.getSprite(PrimaryHitMarker)
                        .setPosition(sf::Vector2f((float) ((128 + (coordinate.getX() * 16)) * 5), (float) ((28 + (coordinate.getY() * 16)) * 5)));
                this->primaryMarkersP2Vector.push_back(resources.getSprite(PrimaryHitMarker));

                resources.getSprite(SecondaryHitMarker)
                        .setPosition(sf::Vector2f((float) ((16 + (coordinate.getX() * 8)) * 5), (float) ((44 + (coordinate.getY() * 8)) * 5)));
                this->secondaryMarkersP1Vector.push_back(resources.getSprite(SecondaryHitMarker));
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
    resources.getSprite(SecondaryTarget).setPosition(sf::Vector2f((float) (16 + (coordinate.getX() * 8) * 5), (float) (44 + (coordinate.getY() * 8) * 5)));
}

void Gameplay::attack(Coordinate &coordinate) {
    if (State::gameMode == State::GameMode::SINGLE_PLAYER) {
        if (State::player == State::Player::P1) {
            SquareType attack = this->gridP2->attack(coordinate);
            if (attack == SquareType::Water) {
                this->updateGridMarkers(attack, coordinate);
                this->render();
                sleepMS();
                State::player = State::Player::P2;
            } else if (attack == SquareType::Ship) {
                this->updateGridMarkers(attack, coordinate);
                this->render();
                sleepMS();
                if (lost(*(this->gridP2))) {
                    this->resetGridMarkers();
                    State::player = State::Player::P2;
                    State::changeScreen(Screens::GameOver);
                } else {
                    State::player = State::Player::P2;
                }
            }
        } else {
            SquareType attack = this->gridP1->attack(coordinate);
            if (attack == SquareType::Water) {
                this->updateGridMarkers(attack, coordinate);
                this->updateSecondaryTarget(coordinate);
                State::player = State::Player::P1;
            } else if (attack == SquareType::Ship) {
                this->updateGridMarkers(attack, coordinate);
                this->updateSecondaryTarget(coordinate);
                if (lost(*(this->gridP1))) {
                    this->resetGridMarkers();
                    State::player = State::Player::P1;
                    State::changeScreen(Screens::GameOver);
                } else {
                    State::player = State::Player::P1;
                }
            }
        }
    } else {
        if (State::player == State::Player::P1) {
            SquareType attack = this->gridP2->attack(coordinate);
            if (attack == SquareType::Water) {
                this->updateGridMarkers(attack, coordinate);
                this->render();
                this->updateSecondaryTarget(coordinate);
                sleepMS();
                State::player = State::Player::P2;
                State::changeScreen(Screens::Intermediary);
            } else if (attack == SquareType::Ship) {
                this->updateGridMarkers(attack, coordinate);
                this->render();
                this->updateSecondaryTarget(coordinate);
                sleepMS();
                if (lost(*(this->gridP2))) {
                    this->resetGridMarkers();
                    State::player = State::Player::P2;
                    State::changeScreen(Screens::GameOver);
                } else {
                    State::player = State::Player::P2;
                    State::changeScreen(Screens::Intermediary);
                }
            }

        } else {
            SquareType attack = this->gridP1->attack(coordinate);
            if (attack == SquareType::Water) {
                this->updateGridMarkers(attack, coordinate);
                this->render();
                this->updateSecondaryTarget(coordinate);
                sleepMS();
                State::player = State::Player::P1;
                State::changeScreen(Screens::Intermediary);
            } else if (attack == SquareType::Ship) {
                this->updateGridMarkers(attack, coordinate);
                this->render();
                this->updateSecondaryTarget(coordinate);
                if (lost(*(this->gridP1))) {
                    sleepMS();
                    this->resetGridMarkers();
                    State::player = State::Player::P1;
                    State::changeScreen(Screens::GameOver);
                } else {
                    sleepMS();
                    State::player = State::Player::P1;
                    State::changeScreen(Screens::Intermediary);
                }
            }
        }
    }
}

void Gameplay::setFleetLayout(shipOrientations &fleetLayout) {
    static const map<int, shipNames> ships = {
            {Battleship, shipNames::Battleship},
            {AircraftCarrier, shipNames::AircraftCarrier},
            {Destroyer, shipNames::Destroyer},
            {Submarine, shipNames::Submarine},
            {PatrolBoat, shipNames::PatrolBoat},
            {RowBoat, shipNames::RowBoat},
    };

    static int xCoord, yCoord, iteration;
    for (auto ship : ships) {
        sf::Sprite &sprite = resources.getSprite(ship.first);
        const shipNames name = ship.second;
        xCoord = get<0>(fleetLayout[name]).getX();
        yCoord = get<0>(fleetLayout[name]).getY();
        iteration = ship.first - Battleship;

        if (get<1>(fleetLayout[name])) {
            sprite.setPosition(sf::Vector2f((float) (64 - 8 * iteration + xCoord * 8) * 5,
                                            (float) (44 + yCoord * 8) * 5));
            sprite.setRotation(90);
        } else {
            sprite.setPosition(sf::Vector2f((float) (16 + xCoord * 8) * 5,
                                            (float) (44 + yCoord * 8) * 5));
            sprite.setRotation(0);
        }
    }
}

void Gameplay::update() {
    sf::Vector2f mousePosition = State::getMousePosition();

    resources.getButton(Surrender).updateButtonState(mousePosition);
    resources.getButton(Instructions).updateButtonState(mousePosition);

    for (auto &target : this->targetVector) {
        target.updateTargetState(mousePosition);
    }

    if (State::gameMode == State::GameMode::SINGLE_PLAYER || State::player == State::Player::P1) {
        this->setFleetLayout(*this->fleetLayoutP1);
    } else {
        this->setFleetLayout(*this->fleetLayoutP2);
    }

    if (State::gameMode == State::GameMode::SINGLE_PLAYER && State::player == State::Player::P2) {
        if (State::difficulty == State::Difficulty::EASY) {
            Coordinate attack = this->randomAttack();
            this->attack(attack);
        } else {
            // TODO: Add hard algorithm
            Coordinate attack = this->randomAttack();
            this->attack(attack);
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
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (resources.getButton(Surrender).getButtonState()) {
                        this->resetGridMarkers();
                        State::changeScreen(Screens::GameOver);
                    } else if (resources.getButton(Instructions).getButtonState()) {
                        State::changeScreen(Screens::Instructions);
                    } else if (!State::lockedFlag) {
                        for (auto &target : this->targetVector) {
                            if (target.getTargetState()) {
                                State::lockedFlag = true;
                                Coordinate targetCoord = target.getTargetCoordinate();
                                this->attack(targetCoord);
                            }
                        }
                    }
                    break;
                }
            default:
                break;
        }
    }
}

void Gameplay::renderSunkShips(Grid &grid) {
    sf::RenderWindow &gui = *State::gui;
    map<shipNames, bool> isSunk = grid.getShipStatus();

    static const map<int, shipNames> ships = {
            {BattleShipSunk, shipNames::Battleship},
            {AircraftCarrierSunk, shipNames::AircraftCarrier},
            {DestroyerSunk, shipNames::Destroyer},
            {SubmarineSunk, shipNames::Submarine},
            {PatrolBoatSunk, shipNames::PatrolBoat},
            {RowBoatSunk, shipNames::RowBoat},
    };

    for (auto ship : ships) {
        const int sunkTexture = ship.first;
        const shipNames name = ship.second;

        if (isSunk[name]) {
            gui.draw(resources.getSprite(sunkTexture));
        }
    }
}

void Gameplay::render() {
    sf::RenderWindow &gui = *State::gui;
    gui.clear();

    // Background rendering
    if (State::gameMode == State::SINGLE_PLAYER) {
        gui.draw(resources.getSprite(BackgroundDefault));
    } else {
        if (State::player == State::Player::P1) {
            gui.draw(resources.getSprite(BackgroundP1));
        } else {
            gui.draw(resources.getSprite(BackgroundP2));
        }
    }

    // Buttons and ships
    resources.getButton(Surrender).render(gui);
    resources.getButton(Instructions).render(gui);

    for (int ship = Battleship; ship <= RowBoat; ++ship) {
        gui.draw(resources.getSprite(ship));
    }

    if (State::gameMode == State::SINGLE_PLAYER || State::player == State::Player::P1) {
        this->renderSunkShips(*(this->gridP2));
    } else {
        this->renderSunkShips(*(this->gridP1));
    }

    // Renders all the target markers
    vector<sf::Sprite> primaryMarkers, secondaryMarkers;
    if (State::gameMode == State::SINGLE_PLAYER || State::player == State::Player::P1) {
        primaryMarkers = primaryMarkersP1Vector;
        secondaryMarkers = secondaryMarkersP1Vector;
    } else {
        primaryMarkers = primaryMarkersP2Vector;
        secondaryMarkers = secondaryMarkersP2Vector;
    }
    for (auto &primaryMarker : primaryMarkers) {
        gui.draw(primaryMarker);
    }
    for (auto &secondaryMarker : secondaryMarkers) {
        gui.draw(secondaryMarker);
    }

    if (State::player == State::Player::P1 && !this->secondaryMarkersP1Vector.empty()) {
        gui.draw(resources.getSprite(SecondaryTarget));
    }
    if (State::player == State::Player::P2 && !this->secondaryMarkersP2Vector.empty()) {
        gui.draw(resources.getSprite(SecondaryTarget));
    }

    for (auto &target : this->targetVector) {
        target.render(gui);
    }

    gui.display();
}

void screen::Gameplay::sleepMS() {
#ifdef _WIN32
    Sleep(sleepTimeMS);
#else
    usleep(sleepTimeMS * 1000);
#endif// _WIN32
}
