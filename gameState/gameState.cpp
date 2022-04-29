#include "gameState.h"

#include <iostream>

#include "../GalacticObjects/planet.h"
#include "../globals/displayMode.h"
#include "../globals/fonts.h"
#include "../utils/utils.h"

GameState::GameState(int windowWidth, int windowHeight) {
    dispMode = DisplayMode::Galaxy;
    galaxyView = sf::View(sf::Vector2f(windowWidth / 2, windowHeight / 2), sf::Vector2f(windowWidth, windowHeight));
    systemView = sf::View(sf::Vector2f(0, 0), sf::Vector2f(windowWidth, windowHeight));
    cameraSpeed = 5;

    stars = Star::loadStars();
    Star::createConnections(stars);
    planets = Planet::loadPlanets(stars);
    empires = Empire::loadEmpires(stars, planets);

    mouseObj = new MouseObj();

    tickNumber = 0;
    milliSecondsPerTick = 1000;
    gameSpeedMultiplier = 1;
    deltaTime = sf::Time::Zero;
    initiateTickNumberText(28, windowWidth);
}

void GameState::handleKeyboardEvent(sf::Event evnt) {
    // std::cout << "a key was pressed " << evnt.key.code << std::endl;

    if (evnt.key.code == sf::Keyboard::Space) {
        if (dispMode == DisplayMode::System) {
            systemView.setCenter(sf::Vector2f(0, 0));
            dispMode = DisplayMode::Galaxy;
            setNewTickNumberTextPosition(galaxyView);
        }
    }
}

void GameState::handleMouseEvent(sf::Event evnt, sf::RenderWindow* window) {
    if (evnt.type == sf::Event::MouseButtonPressed) {
        mouseObj->buttonPressed(evnt.mouseButton.button, evnt.mouseButton.x, evnt.mouseButton.y);
    } else if (evnt.type == sf::Event::MouseButtonReleased) {
        std::cout << "Button Released\n";
        ComplexMouseEvent mouseEvnt =
            mouseObj->buttonReleased(evnt.mouseButton.button, evnt.mouseButton.x, evnt.mouseButton.y);
        std::cout << "got complex mouse event\n";
        if (mouseEvnt.getType() == MouseEventType::Click) {
            if (evnt.mouseButton.button == 0) {
                std::cout << "ClickCoordinate " << evnt.mouseButton.x << "," << evnt.mouseButton.y << std::endl;
                if (dispMode == DisplayMode::Galaxy) {
                    sf::Vector2f transCoord =
                        window->mapPixelToCoords(sf::Vector2i(evnt.mouseButton.x, evnt.mouseButton.y));
                    std::cout << "transformed coordinates" << transCoord.x << "," << transCoord.y << std::endl;
                    Star* clickedStar = getClickedStar(transCoord);
                    if (clickedStar != NULL) {
                        selectedStar = clickedStar;
                        dispMode = DisplayMode::System;
                    }
                }
            }
        }
    }
}

void GameState::handleCameraMovement() {
    if (dispMode == DisplayMode::Galaxy) {
        Utils::moveCamera(&galaxyView, cameraSpeed);
        setNewTickNumberTextPosition(galaxyView);
    } else if (dispMode == DisplayMode::System) {
        Utils::moveCamera(&systemView, cameraSpeed);
        setNewTickNumberTextPosition(galaxyView);
    }
}

sf::View GameState::getGalaxyView() { return galaxyView; }

sf::View GameState::getSystemView() { return systemView; }

Star* GameState::getClickedStar(sf::Vector2f clickCoord) {
    for (std::map<int, Star*>::iterator starIter = stars.begin(); starIter != stars.end(); starIter++) {
        if (starIter->second->inClickArea(clickCoord, dispMode, galaxyView.getCenter())) {
            return starIter->second;
        }
    }
    return NULL;
}

void GameState::update(sf::Time dt) {
    deltaTime = deltaTime + dt * gameSpeedMultiplier;
    while (deltaTime.asMilliseconds() > milliSecondsPerTick) {
        tickNumber++;
        deltaTime = deltaTime - sf::milliseconds(milliSecondsPerTick);
    }
}

void GameState::drawTickNumber(sf::RenderWindow* window) {
    tickNumberText->setString(std::to_string(tickNumber));
    window->draw(*tickNumberText);
}

std::map<int, Star*> GameState::getStars() { return stars; }

void GameState::initiateTickNumberText(int size, int windowWidth) {
    tickNumberText = new sf::Text("", *(AllFonts::getFont()), size);
    tickNumberText->setFillColor(sf::Color::Green);
    tickNumberText->setPosition(sf::Vector2f(0, 0));
    // sf::FloatRect bounds = galacticSprite.getGlobalBounds();
    // sf::Vector2f spriteLoc = galacticSprite.getPosition();
    tickNumberText->setPosition(sf::Vector2f(windowWidth - 50, 0));
}