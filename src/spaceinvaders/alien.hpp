#include <Arduino.h>
#include "../general/gameobject.hpp"

class Alien : public GameObject
{
    public:
        void Setup(int c, int r);

        void Move(float elapsed0) override;

    private:
        int Row;
        int Column;
};