#include "star.h"
#include "../globals/textures.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

Star::Star(std::string name, sf::Vector2f coordinates, std::string spriteName) {
    // sprite
    coords = coordinates;
    this->name = name;


    sf::Texture* starTexture = AllTextures::getTexture(spriteName);
    if (starTexture == NULL) {
        std::cout << "The star texture was null\n";
    }

    systemSprite = sf::Sprite(*starTexture);
    systemSprite.setOrigin(systemSprite.getTextureRect().width/2, systemSprite.getTextureRect().height/2);
    systemSprite.setPosition(0,0);
    systemSprite.setScale(0.2, 0.2);

    galacticSprite = sf::Sprite(*starTexture);
    galacticSprite.setOrigin(galacticSprite.getTextureRect().width/2, galacticSprite.getTextureRect().height/2);
    galacticSprite.setPosition(coords);
    galacticSprite.setScale(0.1, 0.1);

    std::cout << systemSprite.getPosition().x << "\n";
    std::cout << galacticSprite.getPosition().x << "\n";

    std::cout << "The star objectr seems to have been populated properly" << name << std::endl;
}

std::map<int, Star*> Star::loadStars() {
    std::map<int, Star*> starsmap;
    std::cout << "Starting population of stars \n";
    std::string starsFile =
        "gameData/stars.json";  // change to avoid hardcoding

    std::ifstream ifs(starsFile);

    if (ifs.fail()) {
        std::cout << "Failed to read textures.json \n";
        return starsmap;
    }
    nlohmann::json jf = nlohmann::json::parse(ifs);

    if (jf.is_array()) {
        std::cout << "JF is an array\n";
        for (int i = 0; i < jf.size(); i++) {
            int id = jf[i]["id"];
            float x = jf[i]["x"];
            float y = jf[i]["y"];
            std::string name = jf[i]["name"];
            std::string spriteName = jf[i]["sprite"];
            Star* star = new Star(name, sf::Vector2f(x, y), spriteName);
            std::cout << "testing after star creation" << star->galacticSprite.getOrigin().x << std::endl;
            starsmap[id] = star;
        }
    }
    return starsmap;
}
