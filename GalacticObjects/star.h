#ifndef STAR_H
#define STAR_H

#include "galacticDrawable.h"
#include <map>

class Planet;
class Empire;

class Star : public GalacticDrawable {
    std::string name;
    int id;
    std::map<int, Star*> neighbours;
    std::map<int, Planet*> planets;
    Empire* ownedby;
    std::map<int, sf::VertexArray*> neighbourhoodLines;
    sf::ConvexShape domainShape;
public:
    Star(std::string name, sf::Vector2f coordinates, std::string spriteName, int id);
    static std::map<int, Star*> loadStars();
    std::string getName() {return name;};
    static void createConnections(std::map<int, Star*> stars);
    void addNeighbour(int starId, Star* newNeighbour);
    void draw(sf::RenderWindow* window, DisplayMode dispMode);
    void addPlanet(Planet* planet);
    void setEmpire(Empire* emp);
};

#endif