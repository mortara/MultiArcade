#include "tempest_bullet.hpp"
#include "../general/config.h"

TempestBullet::TempestBullet(float angle, float startRadius)
{
    ObjectType = 7;  // 7 = Tempest Bullet
    OutOfBoundsMethod = 2;  // Delete when out of bounds
    Angle = angle;
    RadialDistance = startRadius;
    
    Color = TFT_YELLOW;
    Radius = 2;
    Size = Vector2DF(2, 2);
    
    // Bullets don't use velocity in the traditional sense
    // They move along their lane radially inward
    Velocity = Vector2DF(0, 0);
}
