#include "asteroid.hpp"

void Asteroid::Setup(int s, int sw, int sh)
{
    Sizeclass = s;
    OutOfBoundsMethod = 1;  // 1 = returns on other side
    ObjectType = 2;    // 2 = Asteroid
    Color = TFT_DARKGREY;
    // The shape of the asteroid is generated randomly

    // Random size
    double scale = s * (0.5f + (float)random(4) / 10.0f);

    int points = s * 5;
    Vector2DF *p = new Vector2DF[points];
    float start = 0.5f + (float)random(50) / 100.0f;
    p[0] = Vector2DF(0, start) * scale;

    for(int i = 1; i < points; i++)
    {
        float angle = degreesToRadians(360.0f / points * (float)i);
        float l = 3.0f + (float)random(200) / 100.0f;
        p[i].X = cos(angle) * l * scale;
        p[i].Y = sin(angle) * l * scale;
    }


    // roughly determining a box around the shape, for collision checks
    int minx = 0;
    int maxx = 0;
    int miny = 0;
    int maxy = 0;
    for(int i = 0; i < points; i++)
    {
        if(p[i].X > maxx)
            maxx = p[i].X;

        if(p[i].X < minx)
            minx = p[i].X;

        if(p[i].Y > maxy)
            maxy = p[i].Y;

        if(p[i].Y < miny)
            miny = p[i].Y;
    }

    Size.X = maxx + abs(minx);
    Size.Y = maxy + abs(miny);
    
    // Random initial orientation
    Orientation = random(360);

    // A random starting position, not in the center of the screen
    float w = degreesToRadians(random(360));
    float d = 30 + random(90);
    Position.X = sw + cos(w) * d;
    Position.Y = sh + sin(w) * d;

    // Random starting velocity
    Velocity = Vector2DF(random(40) - 20, random(40) - 20);
   
    // Random rotation speed
    vR = random(60) - 30;

    GameObject::Setup(points, p);
}