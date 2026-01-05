#ifndef TEMPEST_PLAYER_H
#define TEMPEST_PLAYER_H

#include <Arduino.h>
#include "../general/gameobject.hpp"
#include "../Input/rotary_encoder.hpp"

class TempestPlayer : public GameObject
{
    public:
        TempestPlayer(RotaryEncoder *rotary);
        
        bool Control();
        bool FirePressed();
        bool SuperZapperPressed();
        
        float Angle;  // Position around the rim (0-360 degrees)
        
    private:
        RotaryEncoder *_rotary;
        int16_t _lastCount;
        float _rotationSpeed = 5.0f;  // Degrees per encoder tick
};

#endif
