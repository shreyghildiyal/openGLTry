#ifndef __EMPIRE_H__
#define __EMPIRE_H__

#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include <string>

class Star;
class Planet;

class Empire {
    int id;
    std::string name;
    std::map<int, Star*> controlledStars;
    Planet* capital;
    sf::Color color;

    public:
    static std::map<int, Empire*> loadEmpires(std::map<int, Star*> stars, std::map<int, Planet*> planets);
    Empire(int id, std::string name, std::map<int, Star*> controlledStars, Planet* capital, sf::Color color);
};

#endif // __EMPIRE_H__