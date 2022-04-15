#include <SFML/Graphics.hpp>
#include <iostream>

#include "GalacticObjects/star.h"
#include "globals/displayMode.h"
#include <map>
#include "utils/utils.h"

int main() {
    int windowWidth = 600;
    int windowHeight = 600;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFML works!");

    sf::View galaxyView(sf::Vector2f(windowWidth/2, windowHeight/2), sf::Vector2f(windowWidth, windowHeight));
    sf::View systemView(sf::Vector2f(0, 0), sf::Vector2f(windowWidth, windowHeight));

    std::map<int, Star*> stars = Star::loadStars();

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
            } else if (evnt.type == sf::Event::Resized) {
                std::cout << "Resize happened\n";
                galaxyView.setSize(sf::Vector2f(evnt.size.width, evnt.size.height));
            } else if (evnt.type == sf::Event::KeyPressed) {
                std::cout << "a key was pressed " << evnt.key.code << std::endl;
                // evnt.key;
                if (evnt.key.code == sf::Keyboard::Space) {
                     std::cout << "switching display mode" << std::endl;
                    if (dispMode == DisplayMode::Galaxy) {
                        // galaxyView.setCenter(sf::Vector2f(0,0));
                        // activeView = galaxyView;
                        dispMode = DisplayMode::System;
                    } else {
                        // galaxyView.setCenter(stars[2]->getCoords());
                        // activeView = systemView;
                        systemView.setCenter(sf::Vector2f(0,0));
                        dispMode = DisplayMode::Galaxy;
                    }
                }
            } else if (evnt.type == sf::Event::MouseButtonPressed) {
                mouseClickStarted[evnt.mouseButton.button] = true;
                mouseDownLocation[evnt.mouseButton.button][0] = evnt.mouseButton.x;
                mouseDownLocation[evnt.mouseButton.button][1] = evnt.mouseButton.y;
                clickBeingHandled = true;
            } else if (evnt.type == sf::Event::MouseMoved && clickBeingHandled) {
                for (int i = 0; i < mouseButtonCount; i++) {
                    mouseClickStarted[i] = false;
                }
            }
        }

        if (dispMode == DisplayMode::Galaxy) {
            Utils::moveCamera(&galaxyView, 5);
        } else if (dispMode == DisplayMode::System) {
            Utils::moveCamera(&systemView, 5);
        }
       

        window.clear();
        if (dispMode == DisplayMode::Galaxy) {
            window.setView(galaxyView);
        } else if (dispMode == DisplayMode::System) {
            window.setView(systemView);
        }
        
        if (dispMode == DisplayMode::Galaxy) {
            for (std::map<int, Star*>::iterator starIter = stars.begin(); starIter != stars.end(); starIter++) {
                starIter->second->draw(&window, dispMode);
            }
        } else {
            
            stars[1]->draw(&window, dispMode);
        }
        
        window.display();
       
        count++;
    }

    return 0;
}