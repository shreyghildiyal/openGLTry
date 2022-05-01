#include "star.h"
#include "planet.h"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include "../globals/textures.h"
#include <math.h>


std::map<int, Planet*> Planet::loadPlanets(std::map<int, Star*> starMap) {
    std::map<int, Planet*> planets;
    std::cout << "Starting planet loading\n";
    std::string planestFile = "staticFiles/gameData/planets.json";

    std::ifstream ifs(planestFile);

    if (ifs.fail()) {
        std::cout << "Failed to read " << planestFile << "\n";
        return planets;
    }

    nlohmann::json jf = nlohmann::json::parse(ifs);

    if (jf.is_array()) {
        std::cout << "JF is an array\n";
        for (int i = 0; i < jf.size(); i++) {
            std::cout << "Creating a planet\n";
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
            planets[id] = planet;
        }
    }

    return planets;
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

    systemSprite = sf::Sprite(*planetTexture);
    systemSprite.setOrigin(systemSprite.getTextureRect().width/2, systemSprite.getTextureRect().height/2);
    systemSprite.setPosition(coords);
    systemSprite.setScale(0.1, 0.1);

    initiateSystemNameText(name, 19);

    orbitRadius = sqrtf(x*x + y*y);
}

int Planet::getId()
{
    return id;
}

void Planet::draw(sf::RenderWindow* window, DisplayMode dispMode)
{
    // std::cout << "using the overriden method for planet\n";
    if (dispMode == DisplayMode::Galaxy) {
       
        std::cout << "We should not be drawing planets in galaxy view. Something went wrong\n";
        // window->draw(galacticSprite);
    } else if (dispMode == DisplayMode::System) {
        sf::CircleShape orbit(orbitRadius);
        orbit.setFillColor(sf::Color::Transparent);
        orbit.setOutlineColor(sf::Color::White);
        orbit.setOutlineThickness(1);
        orbit.setPosition(sf::Vector2f(-orbitRadius, -orbitRadius));
        window->draw(orbit);
        window->draw(systemSprite);
        window->draw(*systemNameText);
    }
}