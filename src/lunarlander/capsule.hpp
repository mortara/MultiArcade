#include <Arduino.h>
#include "../general/gameobject.hpp"
#include "../Input/rotary_encoder.hpp"
#include "ground.hpp"
#include "../sound/sound.hpp"

class Capsule : public GameObject
{
    public:
        explicit Capsule(RotaryEncoder *playerpaddle, Buzzer * buzzer);
        bool Control();

        float Fuel = 1000;
        float FuelMax = 1000;
        
        float Speed();
        float Altitude(Ground *_ground);

    private:
        RotaryEncoder *_rotary;
        int16_t _lastCount;

        float _acceleration = 15;
        float _rotationspeed = 1;
        Buzzer * _buzzer;
        unsigned long _lastBuzz;
        
};