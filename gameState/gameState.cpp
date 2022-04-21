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
    Star::createConnections(stars);

    // for (std::map<int, Star*>::iterator starIter = stars.begin(); starIter != stars.end(); starIter++) {
    //     // starIter->second->draw(window, gameState->getDispMode());
        
    // }

    mouseObj = new MouseObj();
}

void GameState::handleKeyboardEvent(sf::Event evnt) {
    std::cout << "a key was pressed " << evnt.key.code << std::endl;

    if (evnt.key.code == sf::Keyboard::Space) {
        std::cout << "switching display mode" << std::endl;
        if (dispMode == DisplayMode::System) {
            // galaxyView.setCenter(stars[2]->getCoords());
            // activeView = systemView;
            systemView.setCenter(sf::Vector2f(0, 0));
            dispMode = DisplayMode::Galaxy;
        }
    }
}

void GameState::handleMouseEvent(sf::Event evnt, sf::RenderWindow* window) {
    if (evnt.type == sf::Event::MouseButtonPressed) {
        mouseObj->buttonPressed(evnt.mouseButton.button, evnt.mouseButton.x, evnt.mouseButton.y);
    } else if (evnt.type == sf::Event::MouseButtonReleased) {
        std::cout << "Button Released\n";
        ComplexMouseEvent mouseEvnt = mouseObj->buttonReleased(evnt.mouseButton.button, evnt.mouseButton.x, evnt.mouseButton.y);
        std::cout << "got complex mouse event\n";
        if (mouseEvnt.getType() == MouseEventType::Click) {
            if (evnt.mouseButton.button == 0) {
                std::cout << "ClickCoordinate " << evnt.mouseButton.x << "," << evnt.mouseButton.y << std::endl;
                if (dispMode == DisplayMode::Galaxy) {
                    sf::Vector2f transCoord = window->mapPixelToCoords(sf::Vector2i(evnt.mouseButton.x, evnt.mouseButton.y));
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
    } else if (dispMode == DisplayMode::System) {
        Utils::moveCamera(&systemView, cameraSpeed);
    }
}

sf::View GameState::getGalaxyView() { return galaxyView; }

sf::View GameState::getSystemView() { return systemView; }

Star* GameState::getClickedStar(sf::Vector2f clickCoord)
{
    for (std::map<int, Star *>::iterator starIter = stars.begin(); starIter != stars.end(); starIter++) {
        if (starIter->second->inClickArea(clickCoord, dispMode, galaxyView.getCenter())) {
            return starIter->second;
        }
    }
    return NULL;
}

void GameState::update()
{
    
}

std::map<int, Star*> GameState::getStars() {
    return stars;
}