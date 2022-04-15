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
public:
    void draw(sf::RenderWindow* window, DisplayMode dispMode);
    sf::Vector2f getCoords();
};

#endif