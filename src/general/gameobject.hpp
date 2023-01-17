#include <Arduino.h>
#include <TFT_eSPI.h>
#include "vector2DF.hpp"
#include "config.h"

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class GameObject
{
    public:

        Vector2DF Position;
        Vector2DF OldPosition;

        Vector2DF Velocity;
        Vector2DF Acceleration;

        Vector2DF Size;
    
        float Rotation;
        float vR;

        int16_t OutOfBoundsMethod = 0;
        int16_t ObjectType;

        void Setup(int16_t numpoints, Vector2DF *points);
        void Move(float d);
        void Render(TFT_eSPI _screen, bool force = false);
        void RemoveFromScreen(TFT_eSPI _screen);
        bool Intersects(GameObject * go2);
    private:
        
        int16_t _numPoints = 0;
        Vector2DF *_points;
        Vector2DF *_rotatedpoints;

        void RenderLines(TFT_eSPI screen, int16_t color, float cx, float cy, float rotation);

        float c;
        float s;

        float Rold;
        
};

#endif