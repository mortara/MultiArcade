#include <Arduino.h>
#include "../general/gameobject.h"

class Asteroid:public GameObject
{
    public:
        void Setup(int size);

    private:
        int16_t sizeclass;

};