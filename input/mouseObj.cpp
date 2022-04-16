#include "mouseObj.h"

void MouseObj::buttonPressed(int buttonNumber, int x, int y)
{
    buttonPressLocation[buttonNumber][0] = x;
    buttonPressLocation[buttonNumber][1] = y;
}

bool MouseObj::buttonReleased(int buttonNumber, int x, int y){
    if (buttonPressLocation[buttonNumber][0] == x && buttonPressLocation[buttonNumber][1] == y) {
        return true;
    } else {
        return false;
    }
}

