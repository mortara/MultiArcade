#ifndef TEMPEST_BULLET_H
#define TEMPEST_BULLET_H

#include <Arduino.h>
#include "../general/gameobject.hpp"

class TempestBullet : public GameObject
{
    public:
        TempestBullet(float angle, float startRadius);
        
        float Angle;  // Which lane (0-360 degrees)
        float RadialDistance;  // Distance from center in pixels (CENTER_RADIUS to RIM_RADIUS)
        
    private:
        float _speed = 100.0f;  // Pixels per second moving inward
};

#endif
