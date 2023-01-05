#include <Arduino.h>

class Joystick
{
    public:
        void Setup();
        void Loop();

        int X = 0;
        int Y = 0;
        int SW = 0;
};