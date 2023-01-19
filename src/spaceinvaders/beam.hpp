#include <Arduino.h>
#include "../general/gameobject.hpp"

class Beam : public GameObject
{
    public:
        void Setup(GameObject *start);     

    private:
        float _speed = 150;  
};