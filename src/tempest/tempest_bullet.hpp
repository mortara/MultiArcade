#ifndef TEMPEST_BULLET_H
#define TEMPEST_BULLET_H

#include <Arduino.h>
#include "../general/gameobject.hpp"

class TempestBullet : public GameObject
{
    public:
        TempestBullet(float angle, float startRadius);
        
        float Angle;  // Which lane (0-360 degrees)
        float RadialDistance;  // Distance from center (0-1, where 1 is rim)
        
    private:
        float _speed = 100.0f;  // Pixels per second moving inward
};

#endif
