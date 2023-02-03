#include <Arduino.h>
#include "../general/gameobject.hpp"

#ifndef DEBRIS_H
#define DEBRIS_H

class Debris : public GameObject
{
    public:
        explicit Debris(GameObject *starter);
        void Move(float d) override ;

    private:
        float _lifespan = 2.0;
};

#endif