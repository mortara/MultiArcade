#include "bullet.h"

void Bullet::Setup(GameObject *starter)
{
        ObjectType = 3;
        OutOfBoundsMethod = 2;
        Size = 1;
        w = 1;
        h = 1;

        float r = (starter->Rotation + 90.0f) / 360.0f * 2.0f * PI;

        Position.X = starter->Position.X + cos(r) * 4.0f;
        Position.Y = starter->Position.Y + sin(r) * 4.0f;

        vX = starter->vX + cos(r) * _speed;
        vY = starter->vY + sin(r) * _speed;

        
}