#include <Arduino.h>
#include "../general/gameobject.hpp"

class Alien : public GameObject
{
    public:
        void Setup(int c, int r, int num_cols, TFT_eSPI* screen);

        void Move(float elapsed) override;
        int Row;
        int Column;
    private:
        
        float c;
        float X;
};