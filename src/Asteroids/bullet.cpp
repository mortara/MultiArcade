#include "bullet.h"

void Bullet::Setup(GameObject *starter)
{
        ObjectType = 3;
        OutOfBoundsMethod = 2;
        Size = Vector2DF(1,1);


        float r = (starter->Rotation + 90.0f) / 360.0f * 2.0f * PI;

        Position.X = starter->Position.X + cos(r) * 4.0f;
        Position.Y = starter->Position.Y + sin(r) * 4.0f;

        Velocity.X = starter->Velocity.X + cos(r) * _speed;
        Velocity.Y = starter->Velocity.Y + sin(r) * _speed;

        
}