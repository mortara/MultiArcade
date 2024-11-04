#include "cannonball.hpp"

CannonBall::CannonBall(GameObject *starter, float power)
{
        ObjectType = 3;
        OutOfBoundsMethod = 0;
        Size = Vector2DF(1,1);
        Radius = 1;
        Color = TFT_YELLOW;

        float r = degreesToRadians(starter->GetOrientation() + 90.0f);

        Position.X = starter->Position.X + cos(r) * 4.0f;
        Position.Y = starter->Position.Y + sin(r) * 4.0f;

        Velocity.X = starter->Velocity.X + cos(r) * _speed * power;
        Velocity.Y = starter->Velocity.Y + sin(r) * _speed * power;  
}