#include <Arduino.h>
#include "../general/gameobject.h"
#include "../Input/rotary_encoder.h"

class Ship : public GameObject
{
    public:
        void Setup(RotaryEncoder *playerpaddle);
        bool Control();

    private:
        RotaryEncoder *_rotary;
        int16_t _lastCount;

        float _acceleration = 45;
        float _rotationspeed = 7;
        
};