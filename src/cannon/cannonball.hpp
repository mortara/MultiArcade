#include <Arduino.h>
#include "../general/gameobject.hpp"

class CannonBall: public GameObject
{
    public:
        explicit CannonBall(GameObject *start, float power);     

    private:
        float _speed = 1;  
};