#ifndef __FONTS_H__
#define __FONTS_H__
#include <SFML/Graphics.hpp>
#include <string>


class AllFonts {

    static sf::Font font;
    static const std::string fontFile;
    public:
    static void loadFonts();
    static sf::Font* getFont();
};

#endif // __FONTS_H__