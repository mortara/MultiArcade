#include <math.h>
#include "capsule.hpp"
#include "../general/vector2DF.hpp"

Capsule::Capsule(RotaryEncoder *p1paddle)
{
    _rotary = p1paddle;
    _lastCount = _rotary->Counter;
    OutOfBoundsMethod = 1;
    ObjectType = 1;
    double scale = 1.5;
    GameObject::Setup(4, new Vector2DF[4] {Vector2DF(0.0f,4.0f) * scale, Vector2DF(2.0f,-2.0f)* scale, Vector2DF(0.0f,0.0f)* scale, Vector2DF(-2.0f,-2.0f)* scale});
}

bool Capsule::Control()
{
    int paddlecounter = _rotary->Counter;
    int diff = paddlecounter - _lastCount;
    _lastCount = paddlecounter;

    if(diff != 0)
    {
        float nr = this->GetOrientation() + (float)diff * _rotationspeed;
        while(nr >= 360.0f)
            nr -= 360.0f;

        while(nr < 0.0f)
            nr += 360.0f;

        SetOrientation(nr);
    }

    if(_rotary->SW == 0)  // Accelerate
    {
        float r = degreesToRadians(this->GetOrientation() + 90.0f);
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

