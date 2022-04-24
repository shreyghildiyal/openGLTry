#include "galacticDrawable.h"
#include <iostream>
#include "../globals/fonts.h"

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

bool GalacticDrawable::inClickArea(sf::Vector2f clickCoord, DisplayMode dispMode, sf::Vector2f cameraCoords) {
    sf::Sprite sprite;
    if (dispMode == DisplayMode::Galaxy) {
        sprite = galacticSprite;
    } else if (dispMode == DisplayMode::System) {
        sprite = systemSprite;
    } else {
        return false;
    }

    return sprite.getGlobalBounds().contains(clickCoord);

    // return false;
}

void GalacticDrawable::initiateGalaxyNameText(std::string name, int size) {
    galaxyNameText  = new sf::Text(name, *(AllFonts::getFont()), size);
    galaxyNameText->setFillColor(sf::Color::Green);
    galaxyNameText->setPosition(sf::Vector2f(0, 0));
    sf::FloatRect bounds = galacticSprite.getGlobalBounds();
    sf::Vector2f spriteLoc = galacticSprite.getPosition();
    galaxyNameText->setPosition(sf::Vector2f(spriteLoc.x - bounds.width/2, spriteLoc.y + bounds.height/2));
}

void GalacticDrawable::initiateSystemNameText(std::string name, int size) {
    systemNameText  = new sf::Text(name, *(AllFonts::getFont()), size);
    systemNameText->setFillColor(sf::Color::Green);
    systemNameText->setPosition(sf::Vector2f(0, 0));
    sf::FloatRect bounds = systemSprite.getGlobalBounds();
    sf::Vector2f spriteLoc = systemSprite.getPosition();
    systemNameText->setPosition(sf::Vector2f(spriteLoc.x - bounds.width/2, spriteLoc.y + bounds.height/2));
}
