#include "asteroid.h"

void Asteroid::Setup(int s)
{
    sizeclass = s;
    OutOfBoundsMethod = 1;
    ObjectType = 2;
    int points = s * 4;

    VectorF *p = new VectorF[points];

    float start = 0.5f + (float)random(50) / 100.0f;
    
    p[0].X = 0;
    p[0].Y = start;

    for(int i = 1; i < points; i++)
    {
        float angle = (360.0f / points * (float)i) / 360.0f * 2.0f * PI;
        float l = 3.0f + (float)random(200) / 100.0f;
        p[i].X = cos(angle) * l;
        p[i].Y = sin(angle) * l;
    }
    
    Rotation = random(360);

    Size = s * (0.5f + (float)random(4) / 10.0f);

    Position.X = random(160);
    Position.Y = random(128);

    vX = random(10);
    vY = random(10);

    vR = random(30);

    GameObject::Setup(points, p);
}