#ifndef STAR_H
#define STAR_H

#include "galacticDrawable.h"
#include <map>

class Planet;

class Star : public GalacticDrawable {
    std::string name;
    int id;
    std::map<int, Star*> neighbours;
    std::map<int, Planet*> planets;
    sf::Text* systemNameText;
    sf::Text* galaxyNameText;
public:
    Star(std::string name, sf::Vector2f coordinates, std::string spriteName, int id);
    static std::map<int, Star*> loadStars();
    std::string getName() {return name;};
    static void createConnections(std::map<int, Star*> stars);
    void addNeighbour(int starId, Star* newNeighbour);
    void draw(sf::RenderWindow* window, DisplayMode dispMode);
    void addPlanet(Planet* planet);
    void initiateGalaxyNameText(std::string name, int size);
    void initiateSystemNameText(std::string name, int size);
};

#endif