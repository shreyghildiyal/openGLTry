



class MouseObj {
    const int MOUSE_BUTTONCOUNT = 3;
    bool clickStarted[3];
    int buttonPressLocation[3][2];

    public:
    void buttonPressed(int buttonNumber, int x, int y);
    bool buttonReleased(int buttonNumber, int x, int y);
    
};