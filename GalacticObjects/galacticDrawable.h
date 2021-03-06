#ifndef GALACTICDRAWABLE_H
#define GALACTICDRAWABLE_H

#include <SFML/Graphics.hpp>
#include <string>
#include "../globals/displayMode.h"

class GalacticDrawable {
protected:
    sf::Vector2f coords;
    sf::Sprite galacticSprite;
    sf::Sprite systemSprite;
    sf::Text* systemNameText;
    sf::Text* galaxyNameText;
public:
    void draw(sf::RenderWindow* window, DisplayMode dispMode);
    sf::Vector2f getCoords();
    bool inClickArea(sf::Vector2f clickCoord, DisplayMode dispMode, sf::Vector2f cameraCoords);
    void initiateGalaxyNameText(std::string name, int size);
    void initiateSystemNameText(std::string name, int size);
};

#endif