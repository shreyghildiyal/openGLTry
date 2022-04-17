#include "mouseObj.h"

void MouseObj::buttonPressed(int buttonNumber, int x, int y)
{
    buttonPressLocation[buttonNumber][0] = x;
    buttonPressLocation[buttonNumber][1] = y;
}

ComplexMouseEvent MouseObj::buttonReleased(int buttonNumber, int x, int y){
    if (buttonPressLocation[buttonNumber][0] == x && buttonPressLocation[buttonNumber][1] == y) {
        return ComplexMouseEvent(MouseEventType::Click, sf::Vector2f(x, y));
    } else {
        return ComplexMouseEvent(MouseEventType::Click, sf::Vector2f(buttonPressLocation[buttonNumber][0], buttonPressLocation[buttonNumber][1]), sf::Vector2f(x, y));
    }
}


ComplexMouseEvent::ComplexMouseEvent(MouseEventType newType, sf::Vector2f newStart, sf::Vector2f newEnd)
{
    type = newType;
    start = newStart;
    end = newEnd;
}

ComplexMouseEvent::ComplexMouseEvent(MouseEventType newType, sf::Vector2f newStart)
{
    type = newType;
    start = newStart;
    end = newStart;
}
