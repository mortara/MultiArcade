#include <Arduino.h>
#include "../general/gameobject.hpp"
#include "../Input/rotary_encoder.hpp"

class Player : public GameObject
{
    public:
        void Setup(RotaryEncoder *playerpaddle, TFT_eSPI* screen);
        bool Control();
    private:
        RotaryEncoder *_rotary;
        int16_t _lastCount;
        float _speed = 2;
};
