#include "beam.h"

void Beam::Setup(GameObject *starter)
{
        ObjectType = 3;
        OutOfBoundsMethod = 2;
        Size = Vector2DF(1,5);
        Radius = 5;
        Color = TFT_YELLOW;

        float r = degreesToRadians(starter->GetOrientation() + 90.0f);

        Position = starter->Position;

        Velocity.X = 0;
        Velocity = Vector2DF(0, starter->Velocity.Y + sin(r) * _speed);

        
}