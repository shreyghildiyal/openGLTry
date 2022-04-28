#include "star.h"

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

#include "../empire/empire.h"
#include "../globals/textures.h"
#include "planet.h"
// #include "../globals/fonts.h"

Star::Star(std::string name, sf::Vector2f coordinates, std::string spriteName, int id) {
    // sprite
    coords = coordinates;
    this->name = name;
    this->id = id;

    // sf::Font font = *(AllFonts::getFont());

    sf::Texture* starTexture = AllTextures::getTexture(spriteName);
    if (starTexture == NULL) {
        std::cout << "The star texture was null\n";
    }

    systemSprite = sf::Sprite(*starTexture);
    systemSprite.setOrigin(systemSprite.getTextureRect().width / 2, systemSprite.getTextureRect().height / 2);
    systemSprite.setPosition(0, 0);
    systemSprite.setScale(0.2, 0.2);

    initiateSystemNameText(name, 20);

    galacticSprite = sf::Sprite(*starTexture);
    galacticSprite.setOrigin(galacticSprite.getTextureRect().width / 2, galacticSprite.getTextureRect().height / 2);
    galacticSprite.setPosition(coords);
    galacticSprite.setScale(0.1, 0.1);

    initiateGalaxyNameText(name, 20);

    if (galaxyNameText == NULL) {
        std::cout << "The galaxy name text was NULL\n";
    }

    std::cout << "The star objectr seems to have been populated properly" << name << std::endl;
}

void Star::createConnections(std::map<int, Star*> stars) {
    std::cout << "Starting creation of connections\n";
    std::string connectionFile = "gameData/starConnections.json";

    std::ifstream ifs(connectionFile);

    if (ifs.fail()) {
        std::cout << "Failed to read textures.json \n";
        return;
    }

    nlohmann::json jf = nlohmann::json::parse(ifs);

    if (jf.is_array()) {
        std::cout << "JF is an array\n";
        for (int i = 0; i < jf.size(); i++) {
            nlohmann::json entry = jf[i];
            int starId1 = entry[0];
            int starId2 = entry[1];
            std::cout << "while creating connections found stars " << starId1 << " and " << starId2 << '\n';
            if (stars.find(starId1) != stars.end() && stars.find(starId2) != stars.end()) {
                stars[starId1]->addNeighbour(starId2, stars[starId2]);
                stars[starId2]->addNeighbour(starId1, stars[starId1]);
            } else {
                std::cout << "Error creating connection between " << starId1 << " and " << starId2 << '\n';
            }
        }
    } else {
        std::cout << "file " << connectionFile << " doesnt contain an array\n";
    }
}

void Star::addNeighbour(int starId, Star* newNeighbour) {
    neighbours[starId] = newNeighbour;
    if (starId > id) {
        sf::VertexArray* line = new sf::VertexArray(sf::LineStrip, 2);
        sf::VertexArray line2(sf::LineStrip, 2);
        // line2[0].color
        (*line)[0].position = coords;
        (*line)[0].color = sf::Color::Red;
        (*line)[1].position = newNeighbour->coords;
        (*line)[1].color = sf::Color::Red;
        neighbourhoodLines[starId] = line;
    }
}

std::map<int, Star*> Star::loadStars() {
    std::map<int, Star*> starsmap;
    std::cout << "Starting population of stars \n";
    std::string starsFile = "gameData/stars.json";  // change to avoid hardcoding

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
            int starId = jf[i]["id"];
            Star* star = new Star(name, sf::Vector2f(x, y), spriteName, starId);
            std::cout << "testing after star creation" << star->galacticSprite.getOrigin().x << std::endl;
            starsmap[id] = star;
        }
    }
    return starsmap;
}

void Star::draw(sf::RenderWindow* window, DisplayMode dispMode) {
    if (dispMode == DisplayMode::Galaxy) {
        if (ownedby != NULL) {
            window->draw(domainShape);
        }

        for (auto iter = neighbourhoodLines.begin(); iter != neighbourhoodLines.end(); iter++) {
            window->draw(*(iter->second));
        }
        window->draw(galacticSprite);
        window->draw(*galaxyNameText);
    } else if (dispMode == DisplayMode::System) {
        window->draw(systemSprite);

        window->draw(*systemNameText);

        for (std::map<int, Planet*>::iterator planetIter = planets.begin(); planetIter != planets.end(); planetIter++) {
            planetIter->second->draw(window, dispMode);
        }
    }
}

void Star::addPlanet(Planet* planet) { planets[planet->getId()] = planet; }

void Star::setEmpire(Empire* emp) {
    this->ownedby = emp;
    sf::Color colour = emp->getColour();
    initDomainShape(colour);
}

void Star::initDomainShape(sf::Color colour) {
    colour.a = 100;
    domainShape.setFillColor(colour);
    domainShape.setPointCount(4);
    domainShape.setPoint(0, coords + sf::Vector2f(30, 30));
    domainShape.setPoint(1, coords + sf::Vector2f(30, -30));
    domainShape.setPoint(2, coords + sf::Vector2f(-30, -30));
    domainShape.setPoint(3, coords + sf::Vector2f(-30, 30));
}