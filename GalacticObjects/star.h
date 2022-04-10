#ifndef STAR_H
#define STAR_H

#include "galacticDrawable.h"

class Star : public GalacticDrawable {
    
public:
    Star(std::string name, sf::Vector2f coordinates);
};

#endif