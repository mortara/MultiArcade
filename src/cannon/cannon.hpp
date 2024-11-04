#include <Arduino.h>
#include "../general/gameobject.hpp"
#include "../Input/rotary_encoder.hpp"
#include "CannonGround.hpp"
#include "../sound/sound.hpp"

class Cannon : public GameObject
{
    public:
        explicit Cannon(RotaryEncoder *playerpaddle,Buzzer * buzzer);
        bool Control();
        float Power();
        int Inputmode = 0;
    private:
        RotaryEncoder *_rotary;
        
        int16_t _lastCount;
      
        float _rotationspeed = 5;
        float angle = 45;
        float power = 10;
        Buzzer * _buzzer;
        unsigned long _lastBuzz;
        
};