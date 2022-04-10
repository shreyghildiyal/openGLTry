#include "textures.h"


AllTextures* AllTextures::texturesObject = NULL;

sf::Texture* AllTextures::getTexture(std::string textureName)
{
    // return texturesObject->texturesMap["star"];
    if (texturesObject == NULL) {
        texturesObject = new AllTextures();
        texturesObject->texturesMap["star"] = getStarTexture();
    }
    return texturesObject->texturesMap[textureName];
    // return NULL;
}

sf::Texture* AllTextures::getStarTexture() {
    sf::Texture* texture = new sf::Texture;
    texture->loadFromFile("/mnt/d/cppProjects/openGLTry/sprites/planet1.png"); // find a better solution to full path
    return texture;
}

AllTextures::AllTextures() {
    
}