#include <math.h>
#include "cannon.hpp"
#include "../general/vector2DF.hpp"

Cannon::Cannon(RotaryEncoder *p1paddle, Buzzer *buzzer)
{
    _rotary = p1paddle;
    
    _lastCount = _rotary->GetCounter();
    
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

    if(Inputmode == 0)
    {
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
    }
    else if(Inputmode == 1)
    {
        if(diff != 0)
        {
            power += diff;
            if(power < 1)
                power = 1;

            if(power > 100)
                power = 100;
        }
    }

    if(_rotary->SW == 0)
    {
        Inputmode++;
        if(Inputmode == 2)
            Inputmode = 0;

        delay(500);
    }

    if(_rotary->SW2 == 0)  // Fire
        return true;

    return false;
}