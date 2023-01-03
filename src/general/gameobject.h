#include "../screen/screen.h"

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
        void Render(Screen* _screen);

};