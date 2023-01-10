#include <Arduino.h>
#include <TFT_eSPI.h>
#include "vector.h"
#include "config.h"

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class GameObject
{
    public:

        VectorF Position;
       
        float Size = 1;
        float w = 1;
        float h = 1;

        float aX;
        float aY;

        float vX;
        float vY;

        float Rotation;
        float vR;

        int16_t OutOfBoundsMethod = 0;
        int16_t ObjectType;

        void Setup(int16_t numpoints, VectorF *points);
        void Move(float d);
        void Render(TFT_eSPI _screen);
        void RemoveFromScreen(TFT_eSPI _screen);
      
    private:
        
        int16_t _numPoints = 0;
        VectorF *_points;
        VectorF *_rotatedpoints;

        void RenderLines(TFT_eSPI screen, int16_t color, float cx, float cy, float rotation);

        float c;
        float s;

        float Xold;
        float Yold;
        float Rold;
        
};

#endif