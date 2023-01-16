#include <math.h>
#include "ship.h"

void Ship::Setup(RotaryEncoder *p1paddle)
{
    _rotary = p1paddle;
    Size = 2;
    OutOfBoundsMethod = 1;
    ObjectType = 1;
    GameObject::Setup(4, new VectorF[4] {VectorF(0.0f,4.0f), VectorF(2.0f,-2.0f), VectorF(0.0f,0.0f), VectorF(-2.0f,-2.0f)});
}

bool Ship::Control()
{
    int paddlecounter = _rotary->Counter;
    int diff = paddlecounter - _lastCount;
    _lastCount = paddlecounter;

    if(diff != 0)
    {
        float nr = Rotation + (float)diff * _rotationspeed;
        while(nr >= 360.0f)
            nr -= 360.0f;

        while(nr < 0.0f)
            nr += 360.0f;

        Rotation = nr;
    }

    if(_rotary->Switch1Pressed)  // Accelerate
    {
        float r = (Rotation + 90.0f) / 360.0f * 2.0f * PI;

        aX = cos(r) * _acceleration;
        aY = sin(r) * _acceleration;
    }
    else
    {
        aX = 0;
        aY = 0;
    }

    if(_rotary->Switch2Pressed)  // Fire
        return true;

    return false;
}

