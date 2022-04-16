#include <SFML/Graphics.hpp>
#include <iostream>

#include "GalacticObjects/star.h"
#include "globals/displayMode.h"
#include "gameState/gameState.h"
#include <map>
#include "utils/utils.h"

int main() {
    int windowWidth = 600;
    int windowHeight = 600;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFML works!", sf::Style::Titlebar | sf::Style::Close );

    GameState gameState(windowWidth, windowHeight);

    int count = 0;

    DisplayMode dispMode = DisplayMode::Galaxy;

    const int mouseButtonCount = 3;
    bool mouseClickStarted[mouseButtonCount];
    int mouseDownLocation[3][2];
    bool clickBeingHandled = false;
    bool dragBeingHandled = true;

    while (window.isOpen()) {
        sf::Event evnt;
        while (window.pollEvent(evnt)) {
            if (evnt.type == sf::Event::Closed) {
                window.close();
            } else if (evnt.type == sf::Event::KeyPressed) {
                gameState.handleKeyboardEvent(evnt);
                
            } else if (evnt.type == sf::Event::MouseButtonPressed || evnt.type == sf::Event::MouseButtonReleased || evnt.type == sf::Event::MouseMoved) {
                gameState.handleMouseEvent(evnt);
            }
        }

        window.clear();
        if (dispMode == DisplayMode::Galaxy) {
            window.setView(gameState.getGalaxyView());
        } else if (dispMode == DisplayMode::System) {
            window.setView(gameState.getSystemView());
        }
        
        if (dispMode == DisplayMode::Galaxy) {
            std::map<int, Star *> tempStars = gameState.getStars();
            for (std::map<int, Star*>::iterator starIter = tempStars.begin(); starIter != tempStars.end(); starIter++) {
                // std::cout << "star id from iterator " << starIter->first << std::endl;
                // if (starIter->second == NULL) {
                //     std::cout << "one of the star object pointers is pointing to null\n";
                // } else {
                //     std::cout << "Drawing star " << starIter->second->getName() << std::endl;
                // }
                // std::cout << "checking null " << (starIter->second == NULL) << std::endl;
                
                starIter->second->draw(&window, dispMode);
            }
        } else {
            
            gameState.getStars()[1]->draw(&window, dispMode);
        }
        
        window.display();
       
        count++;
    }

    return 0;
}