#ifndef TEMPEST_ENEMY_H
#define TEMPEST_ENEMY_H

#include <Arduino.h>
#include "../general/gameobject.hpp"

class TempestEnemy : public GameObject
{
    public:
        TempestEnemy(float angle, int level);
        
        float Angle;  // Which lane (0-360 degrees)
        float RadialDistance;  // Distance from center (0-1, where 1 is rim)
        
    private:
        float _speed = 15.0f;  // Base speed - pixels per second moving outward
};

#endif
