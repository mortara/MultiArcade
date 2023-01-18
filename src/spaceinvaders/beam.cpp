#include "beam.h"

void Beam::Setup(GameObject *starter)
{
        ObjectType = 3;
        OutOfBoundsMethod = 2;
        Size = Vector2DF(1,5);
        Radius = 5;
        Color = TFT_YELLOW;

        Position = starter->Position;
        Velocity = Vector2DF(0, _speed);
}