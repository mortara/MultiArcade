#include <Arduino.h>
#include "../general/gameobject.hpp"
#include "../Input/rotary_encoder.hpp"
#include "CannonGround.hpp"
#include "../sound/sound.hpp"

class Cannon : public GameObject
{
    public:
        explicit Cannon(RotaryEncoder *playerpaddle,RotaryEncoder *playerpaddle2, Buzzer * buzzer);
        bool Control();
        float Power();

    private:
        RotaryEncoder *_rotary;
        RotaryEncoder *_rotary2;
        int16_t _lastCount;
        int16_t _lastCount2;
        float _rotationspeed = 5;
        float angle = 45;
        float power = 10;
        Buzzer * _buzzer;
        unsigned long _lastBuzz;
        
};