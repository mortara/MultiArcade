#include <Arduino.h>
#include "../general/gameobject.hpp"

class Bullet: public GameObject
{
    public:
        explicit Bullet(GameObject *start);     

    private:
        float _speed = 120;  
};