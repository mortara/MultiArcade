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
        static constexpr float START_RADIUS = 0.1f;
        static constexpr float BASE_SPEED = 15.0f;
        static constexpr float SPEED_INCREASE_PER_LEVEL = 1.5f;
        
        float _speed = BASE_SPEED;
};

#endif
