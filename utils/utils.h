#ifndef __UTILS_H__
#define __UTILS_H__

#include <SFML/Graphics.hpp>

class Utils {

public:
    static void moveCamera(sf::View* view, float speed);
};
#endif // __UTILS_H__