#include "star.h"
#include "../globals/textures.h"
#include <iostream>

Star::Star(std::string name, sf::Vector2f coordinates) {
    // sprite
    coords = coordinates;
    this->name = name;


    sf::Texture* starTexture = AllTextures::getTexture("star");
    if (starTexture == NULL) {
        std::cout << "The star texture was null\n";
    }

    systemSprite = sf::Sprite(*starTexture);
    systemSprite.setPosition(0,0);

    galacticSprite = sf::Sprite(*starTexture);
    galacticSprite.setPosition(coords);
}
