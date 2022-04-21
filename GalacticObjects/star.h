#ifndef STAR_H
#define STAR_H

#include "galacticDrawable.h"
#include <map>

class Star : public GalacticDrawable {
    std::string name;
    int id;
    std::map<int, Star*> neighbours;
public:
    Star(std::string name, sf::Vector2f coordinates, std::string spriteName, int id);
    static std::map<int, Star*> loadStars();
    std::string getName() {return name;};
    static void createConnections(std::map<int, Star*> stars);
    void addNeighbour(int starId, Star* newNeighbour);
    void draw(sf::RenderWindow* window, DisplayMode dispMode);
};

#endif