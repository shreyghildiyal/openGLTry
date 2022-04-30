#include "utils.h"

bool Utils::moveCamera(sf::View* view, float speed) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        view->setCenter(view->getCenter() + sf::Vector2f(-speed, 0));
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        view->setCenter(view->getCenter() + sf::Vector2f(speed, 0));
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        view->setCenter(view->getCenter() + sf::Vector2f(0, -speed));
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        view->setCenter(view->getCenter() + sf::Vector2f(0, speed));
    } else {
        return false;
    }
    return true;
}
