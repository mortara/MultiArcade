#include <math.h>
#include "ship.h"

void Ship::Setup(RotaryEncoder *p1paddle)
{
    _rotary = p1paddle;

    GameObject::Setup(5, new VectorF[5] {VectorF(0,4), VectorF(2,-2), VectorF(0,0), VectorF(-2-2), VectorF(0,4)});
}

void Ship::Control()
{
    int paddlecounter = _rotary->Counter;
    int diff = paddlecounter - _lastCount;
    _lastCount = paddlecounter;

    this->Rotation += diff;
    while(Rotation >= 360)
        Rotation -=360;

    while(Rotation < 0)
        Rotation+=360;

    if(_rotary->SW == 0)  // Accelerate
    {
        aX = cosf(this->Rotation) * _acceleration;
        aY = sinf(this->Rotation) * _acceleration;

    }

    if(_rotary->SW2 == 0)  // Fire
    {


    }
}

