#include <Arduino.h>
#include "../general/gameobject.h"

class Bullet: public GameObject
{
    public:
        void Setup(GameObject *start);     

    private:
        float _speed = 100;  
};