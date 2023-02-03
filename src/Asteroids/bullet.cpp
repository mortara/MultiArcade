#include "bullet.hpp"

Bullet::Bullet(GameObject *starter)
{
        ObjectType = 3;
        OutOfBoundsMethod = 2;
        Size = Vector2DF(1,1);
        Radius = 1;
        Color = TFT_YELLOW;

        float r = degreesToRadians(starter->GetOrientation() + 90.0f);

        Position.X = starter->Position.X + cos(r) * 4.0f;
        Position.Y = starter->Position.Y + sin(r) * 4.0f;

        Velocity.X = starter->Velocity.X + cos(r) * _speed;
        Velocity.Y = starter->Velocity.Y + sin(r) * _speed;

        
}