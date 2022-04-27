#include "empire.h"
#include "../GalacticObjects/star.h"
#include "../GalacticObjects/planet.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>



std::map<int, Empire*> Empire::loadEmpires(std::map<int, Star*> stars, std::map<int, Planet*> planets) {
    std::map<int, Empire*> empires;
    std::cout << "Starting population of stars \n";
    std::string empiresFile =
        "gameData/empires.json";  // change to avoid hardcoding

    std::ifstream ifs(empiresFile);

    if (ifs.fail()) {
        std::cout << "Failed to read textures.json \n";
        return empires;
    }
    nlohmann::json jf = nlohmann::json::parse(ifs);

    if (jf.is_array()) {
        for (int i = 0 ; i < jf.size(); i++) {
            int id = jf[i]["id"];
            std::string name = jf[i]["name"];
            sf::Color colour(jf[i]["colour"]["r"], jf[i]["colour"]["g"], jf[i]["colour"]["b"], jf[i]["colour"]["alpha"]);
            int capitalPlanetId = jf[i]["capital"];
            std::map<int, Star*> controlledStars;
            for (int j = 0; j < jf[i]["stars"].size(); j++) {
                int starId = jf[i]["stars"][j];
                controlledStars[starId] = stars[starId] ;
            }
            std::cout << "Read empire " << id << " from file\n";
            Empire* empire = new Empire(id, name, controlledStars, planets[capitalPlanetId],  colour);
            for (int j = 0; j < jf[i]["stars"].size(); j++) {
                int starId = jf[i]["stars"][j];
                controlledStars[starId]->setEmpire(empire);
            }

        }
    }

    return empires;
}
Empire::Empire(int id, std::string name, std::map<int, Star*> controlledStars, Planet* capital, sf::Color color) {
    this->id = id;
    this->name = name;
    this->controlledStars = controlledStars;
    this->capital = capital;
    this->color = color;
}
