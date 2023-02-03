#include <Arduino.h>
#include "../general/gameobject.hpp"
#include "../Input/rotary_encoder.hpp"

class Player : public GameObject
{
    public:
        Player(RotaryEncoder *playerpaddle, TFT_eSPI* screen);
        bool Control();
    private:
        RotaryEncoder *_rotary = NULL;
        int16_t _lastCount = 0;
        float _speed = 2;
};
