#include "tempest_enemy.hpp"
#include "../general/config.h"

TempestEnemy::TempestEnemy(float angle, int level)
{
    ObjectType = 8;  // 8 = Tempest Enemy
    OutOfBoundsMethod = 0;  // Don't wrap, we'll handle manually
    Angle = angle;
    RadialDistance = START_RADIUS;  // Start near center
    
    Color = TFT_RED;
    Radius = 3;
    Size = Vector2DF(3, 3);
    
    // Increase speed with level
    _speed = BASE_SPEED + (level * SPEED_INCREASE_PER_LEVEL);
    
    // Enemies don't use velocity in the traditional sense
    // They move along their lane radially outward
    Velocity = Vector2DF(0, 0);
}
