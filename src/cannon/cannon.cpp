#include <math.h>
#include "cannon.hpp"
#include "../general/vector2DF.hpp"

Cannon::Cannon(RotaryEncoder *p1paddle, RotaryEncoder *p2paddle, Buzzer *buzzer)
{
    _rotary = p1paddle;
    _rotary2 = p2paddle;
    _lastCount = _rotary->GetCounter();
    _lastCount2 = _rotary2->GetCounter();
    OutOfBoundsMethod = 1;
    ObjectType = 1;
    _buzzer = buzzer;
    double scale = 1.5;
    GameObject::Setup(4, new Vector2DF[4] {Vector2DF(0.0f,4.0f) * scale, Vector2DF(2.0f,-2.0f)* scale, Vector2DF(0.0f,0.0f)* scale, Vector2DF(-2.0f,-2.0f)* scale});
}

float Cannon::Power()
{
    return power;
}

bool Cannon::Control()
{
    int paddlecounter = _rotary->GetCounter();
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
        angle = nr;
    }
  
    int paddlecounter2 = _rotary2->GetCounter();
    int diff2 = paddlecounter2 - _lastCount2;
    _lastCount2 = paddlecounter2;
    if(diff2 != 0)
    {
        power += diff;
        if(power < 1)
            power = 1;

        if(power > 100)
            power = 100;
    }

    if(_rotary->SW2 == 0)  // Fire
        return true;

    return false;
}