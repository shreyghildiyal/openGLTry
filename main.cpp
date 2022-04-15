#include <SFML/Graphics.hpp>
#include <iostream>

#include "GalacticObjects/star.h"
#include "globals/displayMode.h"
#include <map>

int main() {
    int windowWidth = 600;
    int windowHeight = 600;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFML works!");
    // sf::CircleShape shape(100.f);
    // shape.setFillColor(sf::Color::Green);

    // sf::Vector2f vec1(200,200);
    // sf::RectangleShape rect(vec1);
    // sf::Vector2f vec2(200,200);
    // rect.setPosition(vec2);
    // rect.setFillColor(sf::Color::Red);
    sf::View galaxyView(sf::Vector2f(windowWidth/2, windowHeight/2), sf::Vector2f(windowWidth, windowHeight));
    sf::View systemView(sf::Vector2f(windowWidth/2, windowHeight/2), sf::Vector2f(windowWidth, windowHeight));

    // sf::View activeView = galaxyView;
    

    sf::Texture texture;
    if (!texture.loadFromFile(
            "/mnt/d/cppProjects/openGLTry/sprites/planet1.png"))  // find a better solution to full path
    {
        std::cout << "Error laoding image\n";
        window.close();
        return 1;
    }

    // sf::Sprite sprite(texture);

    std::map<int, Star*> stars = Star::loadStars();

    // Star star("star1", sf::Vector2f(100, 100));

    int count = 0;

    DisplayMode dispMode = DisplayMode::Galaxy;

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
            }
        }

        if (dispMode == DisplayMode::Galaxy) {
             if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                galaxyView.setCenter(galaxyView.getCenter() + sf::Vector2f(-5, 0));
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                galaxyView.setCenter(galaxyView.getCenter() + sf::Vector2f(5, 0));
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                galaxyView.setCenter(galaxyView.getCenter() + sf::Vector2f(0, -5));
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                galaxyView.setCenter(galaxyView.getCenter() + sf::Vector2f(0, 5));
            }
        }
       

        window.clear();
        if (dispMode == DisplayMode::Galaxy) {
            window.setView(galaxyView);
        } else if (dispMode == DisplayMode::System) {
            window.setView(systemView);
        }
        // window.draw(shape);
        // window.draw(rect);
        // window.draw(sprite);
        if (dispMode == DisplayMode::Galaxy) {
            for (std::map<int, Star*>::iterator starIter = stars.begin(); starIter != stars.end(); starIter++) {
                starIter->second->draw(&window, dispMode);
            }
        } else {
            
            stars[1]->draw(&window, dispMode);
        }
        
        // star.draw(&window, dispMode);
        window.display();
        // if (count == 2500) {
        //     dispView.move(50, 0);
        //     std::cout << "view moveright\n";
        // } else if (count == 5000) {
        //     dispView.move(-50, 0);
        //     count = 0;
        //     std::cout << "view moveleft\n";
        // }
        count++;
    }

    return 0;
}