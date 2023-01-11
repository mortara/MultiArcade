#include <Arduino.h>
#include "../general/gameobject.h"

class Asteroid:public GameObject
{
    public:
        int16_t Sizeclass;

        void Setup(int size);

    private:
        

};