#include "galacticDrawable.h"
#include <iostream>

void GalacticDrawable::draw(sf::RenderWindow* window, DisplayMode dispMode)
{
    if (dispMode == DisplayMode::Galaxy) {
        // std::cout << "Window exists " << (window != NULL) << "\n";
        // std::cout << "coords " << coords.x << " " << coords.y <<  std::endl;
        // std::cout << "Sprite " << galacticSprite.getScale().x << "\n";
        window->draw(galacticSprite);
    } else if (dispMode == DisplayMode::System) {
        window->draw(systemSprite);
    }
}

sf::Vector2f GalacticDrawable::getCoords()
{
    return coords;
}
