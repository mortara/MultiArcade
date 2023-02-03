#include <Arduino.h>
#include "../general/gameobject.hpp"

class Beam : public GameObject
{
    public:
        explicit Beam(GameObject *start);     

    private:
        float _speed = 150;  
};