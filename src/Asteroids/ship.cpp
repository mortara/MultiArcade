#include <math.h>
#include "ship.hpp"
#include "../general/vector2DF.hpp"

void Ship::Setup(RotaryEncoder *p1paddle)
{
    _rotary = p1paddle;
    OutOfBoundsMethod = 1;
    ObjectType = 1;
    double scale = 2;
    GameObject::Setup(4, new Vector2DF[4] {Vector2DF(0.0f,4.0f) * scale, Vector2DF(2.0f,-2.0f)* scale, Vector2DF(0.0f,0.0f)* scale, Vector2DF(-2.0f,-2.0f)* scale});
}

bool Ship::Control()
{
    int paddlecounter = _rotary->Counter;
    int diff = paddlecounter - _lastCount;
    _lastCount = paddlecounter;

    if(diff != 0)
    {
        float nr = Orientation + (float)diff * _rotationspeed;
        while(nr >= 360.0f)
            nr -= 360.0f;

        while(nr < 0.0f)
            nr += 360.0f;

        Orientation = nr;
    }

    if(_rotary->SW == 0)  // Accelerate
    {
        float r = degreesToRadians(Orientation + 90.0f);
        Acceleration = Vector2DF(cos(r), sin(r)) * _acceleration;
    }
    else
    {
        Acceleration = Vector2DF(0,0);
    }

    if(_rotary->SW2 == 0)  // Fire
        return true;

    return false;
}

