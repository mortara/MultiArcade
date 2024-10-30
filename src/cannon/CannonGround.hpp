#include <Arduino.h>
#include "../general/gameobject.hpp"

#ifndef CANNONGROUND_H
#define CANNONGROUND_H

class CannonGround : public GameObject
{
    public:
        explicit CannonGround(int mountains, int mountain_height, int screen_width, int screen_height);

        Vector2DF CannonPlatformLocation;
        Vector2DF TargetPlatformLocation;

    private:
        int _peaks;
        
        int _platformSize =  20;

};

#endif