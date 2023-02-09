#include <Arduino.h>
#include "../general/gameobject.hpp"

class Ground : public GameObject
{
    public:
        explicit Ground(int mountains);
};