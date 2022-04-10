#include <SFML/Graphics.hpp>
#include <iostream>
#include "GalacticObjects/star.h"
#include "globals/displayMode.h"

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
    sf::View dispView(sf::Vector2f(0, 0), sf::Vector2f(windowWidth, windowHeight));

    sf::Texture texture;
    if (!texture.loadFromFile("/mnt/d/cppProjects/openGLTry/sprites/planet1.png")) // find a better solution to full path
    {
        std::cout << "Error laoding image\n";
        window.close();
        return 1;
    }

    // sf::Sprite sprite(texture);

    Star star("star1", sf::Vector2f(100, 100));

    int count = 0;
    
    while (window.isOpen()) {
        sf::Event evnt;
        while (window.pollEvent(evnt)) {
            if (evnt.type == sf::Event::Closed) {
                window.close();
            } else if (evnt.type == sf::Event::Resized) {
                std::cout << "Resize happened\n";
                dispView.setSize(sf::Vector2f(evnt.size.width, evnt.size.height));
            }
        }

        window.clear();
        window.setView(dispView);
        // window.draw(shape);
        // window.draw(rect);
        // window.draw(sprite);
        star.draw(&window, DisplayMode::Galaxy);
        window.display();
        if (count == 2500) {
            dispView.move(50, 0);
            std::cout << "view moveright\n";
        } else if (count == 5000) {
            dispView.move(-50, 0);
            count = 0;
            std::cout << "view moveleft\n";
        }
        count++;
    }

    return 0;
}