#include <Arduino.h>
#include <TFT_eSPI.h>

class GameObject
{
    public:
        double X;
        double Y;
        double w;
        double h;

        double vX;
        double vY;

        GameObject();
        ~GameObject();

        void Move(double d);
        void Render(TFT_eSPI _screen);

};