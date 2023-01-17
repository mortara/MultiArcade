#include <Arduino.h>
#include "../general/gameobject.hpp"

class Asteroid:public GameObject
{
    public:
        int16_t Sizeclass;

        void Setup(int size, int sw, int sh);

    private:
        

};