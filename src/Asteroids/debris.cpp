#include "debris.hpp"

void Debris::Setup(GameObject *starter)
{
    ObjectType = 4;
    Position = starter->Position;
    Velocity =starter->Velocity * 0.5 + Vector2DF(random(20) - 10, random(20)- 10);

    Vector2DF *p = new Vector2DF[3];
    p[0] = Vector2DF(random(5) - 2.5, random(5) - 2.5);
    p[1] = Vector2DF(random(5) - 2.5, random(5) - 2.5);
    p[2] = Vector2DF(random(5) - 2.5, random(5) - 2.5);

    GameObject::Setup(3, p);
    Orientation= random(360);
    vR = random(50) - 25;
}

void Debris::Move(float d)
{
    _lifespan -= d;

    if(_lifespan <= 0)
        Delete = true;

    if(_lifespan > 2)
        Color = TFT_LIGHTGREY;
    else if(_lifespan > 1)
        Color = TFT_DARKGREY;
    else
        Color = TFT_BLACK;
    
    GameObject::Move(d);
}