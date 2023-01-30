#include "asteroid.hpp"

void Asteroid::Setup(int s, int sw, int sh)
{
    Sizeclass = s;
    OutOfBoundsMethod = 1;  // 1 = returns on other side
    ObjectType = 2;    // 2 = Asteroid
    Color = TFT_DARKGREY;
    // The shape of the asteroid is generated randomly

    // Random size
    float scale = (float)s * (0.5f + (float)random(4) / 10.0f);
    if(scale < 1)
        scale = 1;

    int points = s * 5;
    if(points < 3)
        points = 3;

    Vector2DF *p = new Vector2DF[points];
    for(int i = 0; i < points; i++)
    {
        float angle = degreesToRadians((360.0f / points) * (float)i);
        float l = 3.0f + (float)random(200) / 100.0f;
        p[i].X = cos(angle) * l * scale;
        p[i].Y = sin(angle) * l * scale;
    }

    // Random initial orientation
    SetOrientation(random(360));

    // A random starting position around the given position in sw, sh
    float w = degreesToRadians(random(360));
    float d = 30 + random(60);
    Position.X = sw + cos(w) * d;
    Position.Y = sh + sin(w) * d;

    // Random starting velocity
    Velocity = Vector2DF(random(40) - 20, random(40) - 20);
   
    // Random rotation speed
    vR = random(180) - 90;

    GameObject::Setup(points, p);
}