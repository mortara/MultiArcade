#ifndef TEMPEST_ENEMY_H
#define TEMPEST_ENEMY_H

#include <Arduino.h>
#include "../general/gameobject.hpp"

class TempestEnemy : public GameObject
{
    public:
        TempestEnemy(float angle, int level);
        
        float Angle;  // Which lane (0-360 degrees)
        float RadialDistance;  // Distance from center in pixels (CENTER_RADIUS to RIM_RADIUS)
        float Speed;  // Pixels per second moving outward
        
    private:
        static constexpr float START_RADIUS = 5.0f;  // Start at center in pixels
        static constexpr float BASE_SPEED = 15.0f;
        static constexpr float SPEED_INCREASE_PER_LEVEL = 1.5f;
};

#endif
