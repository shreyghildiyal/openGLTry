#ifndef STAR_H
#define STAR_H

#include "galacticDrawable.h"
#include <map>

class Star : public GalacticDrawable {
    std::string name;
    int id;
public:
    Star(std::string name, sf::Vector2f coordinates, std::string spriteName);
    static std::map<int, Star*> loadStars();
    std::string getName() {return name;};
    static void createConnections(std::map<int, Star*> stars);
};

#endif