#ifndef __GAMESTATE_H__
#define __GAMESTATE_H__

#include <SFML/Graphics.hpp>

#include "../GalacticObjects/star.h"
#include "../empire/empire.h"
#include "../input/mouseObj.h"

class GameState {
    sf::View galaxyView;
    sf::View systemView;
    DisplayMode dispMode;
    float cameraSpeed;
    std::map<int, Star*> stars;
    std::map<int, Planet*> planets;
    MouseObj* mouseObj;
    Star* selectedStar;
    std::map<int, Empire*> empires;

    int tickNumber;
    float gameSpeedMultiplier;
    float milliSecondsPerTick;
    sf::Time deltaTime;
    sf::Text* tickNumberText;

   public:
    GameState(int windowWidth, int windowHeight);
    void handleKeyboardEvent(sf::Event);
    void handleMouseEvent(sf::Event, sf::RenderWindow* window);
    void handleCameraMovement();
    sf::View getGalaxyView();
    sf::View getSystemView();
    std::map<int, Star*> getStars();
    DisplayMode getDispMode() { return dispMode; };
    Star* getClickedStar(sf::Vector2f clickCoord);
    Star* getSelectedStar() { return selectedStar; };
    void update(sf::Time dt);
    void drawTickNumber(sf::RenderWindow* window);
    void initiateTickNumberText(int size, int windowWidth);
};
#endif  // __GAMESTATE_H__