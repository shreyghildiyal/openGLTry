#include "fonts.h"
#include <string>

#include <iostream>

const std::string AllFonts::fontFile = "fonts/BrassMonoRegular-o2Yz.otf";

void loadFont() {
    

    sf::Font font;
    
}
void AllFonts::loadFonts()
{
    bool success = font.loadFromFile(fontFile);
    if (!success)
    {
        std::cout << "Error loading font from " << fontFile << "\n";
    }
}
