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
        float Radius;
    
        
        float vR;

        int PolygonPoints = 0;

        int16_t OutOfBoundsMethod = 0;
        int16_t ObjectType;

        uint32_t Color = TFT_WHITE;

        bool Delete = false;

        void Setup(int16_t numpoints, Vector2DF *points);
        virtual void Move(float d);

        void SetOrientation(float d);
        float GetOrientation();

        void Render(TFT_eSPI _screen, bool force = false);
        void RemoveFromScreen(TFT_eSPI _screen);
        bool OutOfBoundsCheck(TFT_eSPI _screen);
        bool CollidesWith(GameObject * go2);
        bool PointInPolygon(Vector2DF point);

    private:
        Vector2DF *_points;
        Vector2DF *_rotatedpoints;
        Vector2DF *_rendered_points;
        float _orientation;
        float _old_orientation;
        void RenderLines(TFT_eSPI screen, int16_t color, Vector2DF position, Vector2DF *points);
      
        
};

#endif