#include "bullet.h"

void Bullet::Setup(GameObject *starter)
{
        ObjectType = 3;
        OutOfBoundsMethod = 2;
        Size = 1;
        w = 1;
        h = 1;

        Position.X = starter->Position.X;
        Position.Y = starter->Position.Y;

        float r = (starter->Rotation + 90.0f) / 360.0f * 2.0f * PI;
    
        vX = starter->vX + cos(r) * _speed;
        vY = starter->vY + sin(r) * _speed;

        
}