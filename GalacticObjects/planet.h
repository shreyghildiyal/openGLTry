#ifndef __PLANET_H__
#define __PLANET_H__

#include "galacticDrawable.h"
#include <string>

class Star;

class Planet: public GalacticDrawable {

    std::string name;
    int id;
    Star* star;

    public:
    static void loadPlanets(std::map<int, Star*> starMap); 

};
#endif // __PLANET_H__