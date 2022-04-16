#include "gameState.h"

#include <iostream>

#include "../globals/displayMode.h"
#include "../utils/utils.h"

GameState::GameState(int windowWidth, int windowHeight) {
    dispMode = DisplayMode::Galaxy;
    galaxyView = sf::View(sf::Vector2f(windowWidth / 2, windowHeight / 2), sf::Vector2f(windowWidth, windowHeight));
    systemView = sf::View(sf::Vector2f(0, 0), sf::Vector2f(windowWidth, windowHeight));
    cameraSpeed = 5;

    stars = Star::loadStars();
    // mouseObj = MouseObj();
}

void GameState::handleKeyboardEvent(sf::Event evnt) {
    std::cout << "a key was pressed " << evnt.key.code << std::endl;

    if (evnt.key.code == sf::Keyboard::Space) {
        std::cout << "switching display mode" << std::endl;
        if (dispMode == DisplayMode::Galaxy) {
            // galaxyView.setCenter(sf::Vector2f(0,0));
            // activeView = galaxyView;
            dispMode = DisplayMode::System;
        } else {
            // galaxyView.setCenter(stars[2]->getCoords());
            // activeView = systemView;
            systemView.setCenter(sf::Vector2f(0, 0));
            dispMode = DisplayMode::Galaxy;
        }
    }
}

void GameState::handleMouseEvent(sf::Event evnt) {
    if (evnt.type == sf::Event::MouseButtonPressed) {
        mouseObj.buttonPressed(evnt.mouseButton.button, evnt.mouseButton.x, evnt.mouseButton.y);
    } else if (evnt.type == sf::Event::MouseButtonReleased) {
        bool isClick = mouseObj.buttonReleased(evnt.mouseButton.button, evnt.mouseButton.x, evnt.mouseButton.y);
    } 
}

void GameState::handleCameraMovement() {
    if (dispMode == DisplayMode::Galaxy) {
        Utils::moveCamera(&galaxyView, cameraSpeed);
    } else if (dispMode == DisplayMode::System) {
        Utils::moveCamera(&systemView, cameraSpeed);
    }
}

sf::View GameState::getGalaxyView() { return galaxyView; }

sf::View GameState::getSystemView() { return systemView; }

std::map<int, Star*> GameState::getStars() {
    return stars;
}