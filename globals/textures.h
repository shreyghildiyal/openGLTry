#include <map>
#include <SFML/Graphics.hpp>


class AllTextures {

    private:
    static AllTextures *texturesObject;
    std::map<std::string, sf::Texture*> texturesMap;

    AllTextures();
    static sf::Texture* getStarTexture();

    public:
    static sf::Texture* getTexture(std::string textureName);
};