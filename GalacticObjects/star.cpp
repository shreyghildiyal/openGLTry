#include "star.h"
#include "../globals/textures.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include "planet.h"
#include "../globals/fonts.h"

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
    systemSprite.setOrigin(systemSprite.getTextureRect().width/2, systemSprite.getTextureRect().height/2);
    systemSprite.setPosition(0,0);
    systemSprite.setScale(0.2, 0.2);

    initiateSystemNameText(name, 20);

    galacticSprite = sf::Sprite(*starTexture);
    galacticSprite.setOrigin(galacticSprite.getTextureRect().width/2, galacticSprite.getTextureRect().height/2);
    galacticSprite.setPosition(coords);
    galacticSprite.setScale(0.1, 0.1);

    initiateGalaxyNameText(name, 20);

    
    if (galaxyNameText == NULL) {
        std::cout << "The galaxy name text was NULL\n";
    }



    std::cout << "The star objectr seems to have been populated properly" << name << std::endl;
}

void Star::initiateGalaxyNameText(std::string name, int size) {
    galaxyNameText  = new sf::Text(name, *(AllFonts::getFont()), size);
    galaxyNameText->setFillColor(sf::Color::Green);
    galaxyNameText->setPosition(sf::Vector2f(0, 0));
    sf::FloatRect bounds = galacticSprite.getGlobalBounds();
    sf::Vector2f spriteLoc = galacticSprite.getPosition();
    galaxyNameText->setPosition(sf::Vector2f(spriteLoc.x - bounds.width/2, spriteLoc.y + bounds.height/2));
}

void Star::initiateSystemNameText(std::string name, int size) {
    systemNameText  = new sf::Text(name, *(AllFonts::getFont()), size);
    systemNameText->setFillColor(sf::Color::Green);
    systemNameText->setPosition(sf::Vector2f(0, 0));
    sf::FloatRect bounds = systemSprite.getGlobalBounds();
    sf::Vector2f spriteLoc = systemSprite.getPosition();
    systemNameText->setPosition(sf::Vector2f(spriteLoc.x - bounds.width/2, spriteLoc.y + bounds.height/2));
}

void Star::createConnections(std::map<int, Star*> stars) {
    std::cout << "Starting creation of connections\n";
    std::string connectionFile  = "gameData/starConnections.json";

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
            if (stars.find(starId1) != stars.end() && stars.find(starId2) != stars.end() ) {
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
            int starId = jf[i]["id"];
            Star* star = new Star(name, sf::Vector2f(x, y), spriteName, starId);
            std::cout << "testing after star creation" << star->galacticSprite.getOrigin().x << std::endl;
            starsmap[id] = star;
        }
    }
    return starsmap;
}

void Star::draw(sf::RenderWindow* window, DisplayMode dispMode)
{
    // std::cout << "using the overriden method for star\n";
    if (dispMode == DisplayMode::Galaxy) {
        for (std::map<int, Star*>::iterator iter = neighbours.begin(); iter != neighbours.end(); iter++) {
            // std::cout << "star " << id << " neighbour " << iter->first << '\n';
            if (iter->first > id) {
                
                sf::VertexArray lines(sf::LinesStrip, 2);
                lines[0].position = coords;
                lines[0].color = sf::Color::Red;
                lines[1].position = iter->second->coords;
                lines[1].color = sf::Color::Red;
                
                window->draw(lines);

            }
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

void Star::addPlanet(Planet* planet)
{
    planets[planet->getId()] = planet;
}