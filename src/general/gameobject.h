#include <Arduino.h>
#include <TFT_eSPI.h>

class GameObject
{
    public:
        float X;
        float Y;
        float w;
        float h;

        float vX;
        float vY;

        GameObject();
        ~GameObject();

        void Move(float d);
        void Render(TFT_eSPI _screen);

};