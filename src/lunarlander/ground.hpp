#include <Arduino.h>
#include "../general/gameobject.hpp"

#ifndef GROUND_H
#define GROUND_H

class Ground : public GameObject
{
    public:
        explicit Ground(int mountains, int screen_width, int screen_height);

    private:
        int _peaks;
        Vector2DF _platformLocation;
        int _platformSize =  20;

};

#endif