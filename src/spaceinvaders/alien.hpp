#include <Arduino.h>
#include "../general/gameobject.hpp"

class Alien : public GameObject
{
    public:
        Alien(int c, int r, int num_cols, TFT_eSPI* screen);

        void Move(float elapsed) override;
        int Row = 0;
        int Column = 0;

        
    private:
        
        float c = 0;
        float X = 0;
};