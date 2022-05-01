#include "fonts.h"

#include <iostream>
#include <string>

const std::string AllFonts::fontFile = "staticFiles/fonts/BrassMonoRegular-o2Yz.otf";
sf::Font* AllFonts::font = NULL;

void AllFonts::loadFonts() {
    font = new sf::Font();
    bool success = font->loadFromFile(fontFile);
    if (!success) {
        std::cout << "Error loading font from " << fontFile << "\n";
    }
}

sf::Font* AllFonts::getFont() {
    if (font == NULL) {
        loadFonts();
    }
    return font;
}
