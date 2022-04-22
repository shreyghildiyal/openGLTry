#include "star.h"
#include "planet.h"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include "../globals/textures.h"


void Planet::loadPlanets(std::map<int, Star*> starMap) {
    std::string planestFile = "gameData/planets.json";

    std::ifstream ifs(planestFile);

    if (ifs.fail()) {
        std::cout << "Failed to read textures.json \n";
        return;
    }

    nlohmann::json jf = nlohmann::json::parse(ifs);

    if (jf.is_array()) {
        std::cout << "JF is an array\n";
        for (int i = 0; i < jf.size(); i++) {
            nlohmann::json entry = jf[i];
            int id = entry["id"];
            std::string name = entry["name"];
            int starId = entry["star"];
            int x = entry["x"];
            int y = entry["y"];
            std::string spriteName = entry["sprite"];
            std::cout << "Creating planet " << name << " in star system " << starId << '\n'; 
            Planet* planet = new Planet(id, name, starMap[starId], x, y, spriteName);
            starMap[starId]->addPlanet(planet);
        }
    }
}

Planet::Planet(int id, std::string name, Star* inStar, int x, int y, std::string spriteName) {
    this->id = id;
    this->name = name;
    this->star = inStar;
    coords = sf::Vector2f(x, y);

    sf::Texture* planetTexture = AllTextures::getTexture(spriteName);
    if (planetTexture == NULL) {
        std::cout << "The planet texture was null\n";
    }

    galacticSprite = sf::Sprite(*planetTexture);
    galacticSprite.setOrigin(galacticSprite.getTextureRect().width/2, galacticSprite.getTextureRect().height/2);
    galacticSprite.setPosition(coords);
    galacticSprite.setScale(0.1, 0.1);
}

int Planet::getId()
{
    return id;
}
