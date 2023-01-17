#include <Arduino.h>
#include "../general/gameobject.hpp"

class Debris : public GameObject
{
    public:
        void Setup(GameObject *starter);
        void Move(float d) override ;

    private:
        float _lifespan = 2.0;
};