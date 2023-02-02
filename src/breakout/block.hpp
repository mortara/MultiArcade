#include <Arduino.h>
#include "../general/gameobject.hpp"

class Block : public GameObject
{
    public:
        Block(uint16_t color);
        void Render(TFT_eSPI* screen);
        void RemoveFromScreen(TFT_eSPI* screen);

    private:
        uint16_t _color;
        
};