#ifndef __TEXTURES_H__
#define __TEXTURES_H__

#include <map>
#include <SFML/Graphics.hpp>


class AllTextures {

    private:
    std::map<std::string, sf::Texture*> texturesMap;
    static AllTextures *texturesObject;
    static sf::Texture* defaultTexture;
    

    AllTextures();
    void populateTexturesMap();

    public:
    static sf::Texture* getTexture(std::string textureName);
    
};
#endif // __TEXTURES_H__