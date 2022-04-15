#include "textures.h"

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

AllTextures* AllTextures::texturesObject = NULL;
sf::Texture* AllTextures::defaultTexture = NULL;

sf::Texture* AllTextures::getTexture(std::string textureName) {
    
    if (texturesObject == NULL) {
        texturesObject = new AllTextures();
    }
    if (texturesObject->texturesMap.find(textureName) != texturesObject->texturesMap.end()) {
        return texturesObject->texturesMap[textureName];
    } else {
        return defaultTexture;
    }
    
}

void AllTextures::populateTexturesMap() {
    // texturesObject->texturesMap = std::map<std::string, sf::Texture *>();
    std::cout << "Starting population of textures in map \n";
    std::string texturesConfigFile =
        "gameData/textures.json";  // change to avoid hardcoding

    std::ifstream ifs(texturesConfigFile);

    if (ifs.fail()) {
        std::cout << "Failed to read textures.json \n";
        return;
    }
    nlohmann::json jf = nlohmann::json::parse(ifs);

    if (jf.is_object()) {
        std::cout << "JF is an object\n";
        for (nlohmann::detail::iter_impl<nlohmann::json> iter = jf.begin(); iter != jf.end(); iter++) {
            std::cout << "using the iterator\n";
            std::string path = iter.value();
            std::cout << "path " << path << "\n"; 
            sf::Texture* texture = new sf::Texture();
            if (texture->loadFromFile(path)) {
                texturesMap[iter.key()] = texture;
            } else {
                std::cout << "Failed to load texture " << path << std::endl;
            }
        }
    }
    // defaultTexture = new sf::Texture();
}


AllTextures::AllTextures() { populateTexturesMap(); }