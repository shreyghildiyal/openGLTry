#include <SFML/Graphics.hpp>

enum class MouseEventType {
    Click, 
    Drag
};

class ComplexMouseEvent {
    MouseEventType type;
    sf::Vector2f start;
    sf::Vector2f end;

    public:
    ComplexMouseEvent(MouseEventType newType, sf::Vector2f newStart, sf::Vector2f newEnd);
    ComplexMouseEvent(MouseEventType newType, sf::Vector2f newStart);
    MouseEventType getType() {return type;};
};

class MouseObj {
    const int MOUSE_BUTTONCOUNT = 3;
    bool clickStarted[3];
    int buttonPressLocation[3][2];

    public:
    void buttonPressed(int buttonNumber, int x, int y);
    ComplexMouseEvent buttonReleased(int buttonNumber, int x, int y);
    
};