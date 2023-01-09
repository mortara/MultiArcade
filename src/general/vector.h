#include <Arduino.h>

class VectorF
{
    public:
        float X;
        float Y;

        VectorF(float x, float y);

        void Rotate(float rads);

};