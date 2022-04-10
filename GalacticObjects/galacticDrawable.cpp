#include "galacticDrawable.h"


void GalacticDrawable::draw(sf::RenderWindow* window, DisplayMode dispMode)
{
    if (dispMode == DisplayMode::Galaxy) {
        window->draw(galacticSprite);
    } else if (dispMode == DisplayMode::System) {
        window->draw(systemSprite);
    }
}
