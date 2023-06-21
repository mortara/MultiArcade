#include <Arduino.h>
#include "../general/gameobject.hpp"
#include "../Input/rotary_encoder.hpp"

class Ship : public GameObject
{
    public:
        explicit Ship(RotaryEncoder *playerpaddle);
        bool Control();

    private:
        RotaryEncoder *_rotary;
        int16_t _lastCount;

        float _acceleration = 50;
        float _rotationspeed = 10;
        
};