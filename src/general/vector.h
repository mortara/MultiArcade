#include <Arduino.h>

#ifndef VECTORF_H
#define VECTORF_H

class VectorF
{
    public:
        float X;
        float Y;

        VectorF();
        VectorF(float x, float y);

        void Rotate(float rads);
        VectorF GetRotated(float rads);

        float Distance(VectorF v2);
};

#endif