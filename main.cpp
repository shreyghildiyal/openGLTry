#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
#include <map>
#include <thread>

#include "GalacticObjects/star.h"
#include "gameState/gameState.h"
#include "globals/displayMode.h"
#include "globals/fonts.h"
#include "utils/utils.h"
// #include "globals/fonts.h"

void handleInputs(sf::RenderWindow* window, GameState* gameState) {
    sf::Event evnt;
    while (window->pollEvent(evnt)) {
        if (evnt.type == sf::Event::Closed) {
            window->close();
        } else if (evnt.type == sf::Event::KeyPressed) {
            gameState->handleKeyboardEvent(evnt);

        } else if (evnt.type == sf::Event::MouseButtonPressed || evnt.type == sf::Event::MouseButtonReleased) {
            gameState->handleMouseEvent(evnt, window);
        }
    }
    gameState->handleCameraMovement();

    // window->clear();
    // if (gameState.getDispMode() == DisplayMode::Galaxy) {
    //     window.setView(gameState.getGalaxyView());
    // } else if (gameState.getDispMode() == DisplayMode::System) {
    //     window.setView(gameState.getSystemView());
    // }
}

void renderUI(sf::RenderWindow* window, GameState* gameState) {
    gameState->drawTickNumber(window);
    gameState->drawGameSpeedButtons(window);
}

void render(sf::RenderWindow* window, GameState* gameState) {
    window->clear();
    if (gameState->getDispMode() == DisplayMode::Galaxy) {
        window->setView(gameState->getGalaxyView());
    } else if (gameState->getDispMode() == DisplayMode::System) {
        window->setView(gameState->getSystemView());
    }

    if (gameState->getDispMode() == DisplayMode::Galaxy) {
        std::map<int, Star*> tempStars = gameState->getStars();
        for (std::map<int, Star*>::iterator starIter = tempStars.begin(); starIter != tempStars.end(); starIter++) {
            starIter->second->draw(window, gameState->getDispMode());
        }

    } else if (gameState->getDispMode() == DisplayMode::System) {
        if (gameState->getSelectedStar() != NULL) {
            gameState->getSelectedStar()->draw(window, gameState->getDispMode());
        } else {
            std::cout << "there is no selected star\n";
        }
    }

    renderUI(window, gameState);

    window->display();
}

void update(sf::RenderWindow* window, GameState* gameState, sf::Time dt) { gameState->update(dt); }

int main() {
    int windowWidth = 800;
    int windowHeight = 600;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFML works!",
                            sf::Style::Titlebar | sf::Style::Close);
    window.setPosition(sf::Vector2i(300, 200));
    GameState gameState(windowWidth, windowHeight);
    // AllFonts::loadFonts();

    int count = 0;

    sf::Clock deltaClock;
    sf::Time dt;

    // sf::Time dt = deltaClock.Restart();

    while (window.isOpen()) {
        dt = deltaClock.restart();

        handleInputs(&window, &gameState);

        update(&window, &gameState, dt);

        render(&window, &gameState);
        count++;
        // std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}