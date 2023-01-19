#include <Arduino.h>
#include "../general/gameobject.hpp"

class Alien : public GameObject
{
    public:
        void Setup(int c, int r, TFT_eSPI screen);

        void Move(float elapsed) override;

    private:
        int Row;
        int Column;
};