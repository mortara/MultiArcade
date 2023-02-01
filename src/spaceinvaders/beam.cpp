#include "beam.hpp"

void Beam::Setup(GameObject *starter)
{
        ObjectType = 3;
        OutOfBoundsMethod = 2;
        Size = Vector2DF(1,5);
        Radius = 5;
        Color = TFT_YELLOW;
        float length = 4.0;

        if(starter->ObjectType == 1)
        {
            Position = starter->Position - Vector2DF(0, length + 5 );
            Velocity = Vector2DF(0, -_speed);
            length = length * -1.0;
        }
        else
        {
            Position = starter->Position + Vector2DF(0, length + 1 + starter->Size.Y);
            Velocity = Vector2DF(0, _speed);
        }

        float scale = 1;

        GameObject::Setup(2, new Vector2DF[2] 
        {
            Vector2DF(0.0f,length) * scale, 
            Vector2DF(0.0f,0.0f) * scale            
        });
}