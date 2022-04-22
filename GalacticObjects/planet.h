#ifndef __PLANET_H__
#define __PLANET_H__

#include "galacticDrawable.h"
#include <string>

class Star;

class Planet: public GalacticDrawable {

    std::string name;
    int id;
    Star* star;
    float orbitRadius;

    public:
    static void loadPlanets(std::map<int, Star*> starMap); 
    Planet(int id, std::string name, Star* inStar, int x, int y, std::string spriteName);
    int getId();
    void draw(sf::RenderWindow* window, DisplayMode dispMode);
};
#endif // __PLANET_H__