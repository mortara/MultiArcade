#include <Arduino.h>
#include <TFT_eSPI.h>
#include "vector.h"
#include "config.h"

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class GameObject
{
    public:

        float X;
        float Y;
        float w;
        float h;

        float aX;
        float aY;

        float vX;
        float vY;

        float Xold;
        float Yold;

        float Rotation;

        int16_t Enabled;

        void Setup(int16_t numpoints, float *points);
        void Move(float d);
        void Render(TFT_eSPI _screen);

    private:
        
        int16_t _numPoints = 0;
        float *_points;

        void RenderLines(TFT_eSPI screen, int16_t color, float cx, float cy);
};

#endif