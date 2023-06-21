#include <math.h>
#include "capsule.hpp"
#include "../general/vector2DF.hpp"

Capsule::Capsule(RotaryEncoder *p1paddle, Buzzer *buzzer)
{
    _rotary = p1paddle;
    _lastCount = _rotary->GetCounter();
    OutOfBoundsMethod = 1;
    ObjectType = 1;
    _buzzer = buzzer;
    double scale = 1.5;
    GameObject::Setup(4, new Vector2DF[4] {Vector2DF(0.0f,4.0f) * scale, Vector2DF(2.0f,-2.0f)* scale, Vector2DF(0.0f,0.0f)* scale, Vector2DF(-2.0f,-2.0f)* scale});
}

float Capsule::Speed()
{
    return Velocity.Length();
}

float Capsule::Altitude(Ground *_ground)
{
    return Position.Y;
}

bool Capsule::Control()
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
    }
    float _cost = 0.5;
    if((_rotary->SW == 0 || _rotary->SW2 == 0) && Fuel > _cost)  // Accelerate
    {
        float r = degreesToRadians(this->GetOrientation() + 90.0f);
        Acceleration = Vector2DF(cos(r), sin(r)) * _acceleration;
        Fuel -= _cost;

        if(millis() - _lastBuzz > 50)
        {
            _lastBuzz = millis();
            _buzzer->PlayNoise(50);
        }
    }
    else
    {
        Acceleration = Vector2DF(0,0);
    }
    
    return false;
}

