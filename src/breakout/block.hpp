#include <Arduino.h>
#include "../general/gameobject.h"

class Block : public GameObject
{
    public:
        void Setup(uint16_t color);
        void Render(TFT_eSPI screen);
        void RemoveFromScreen(TFT_eSPI screen);

    private:
        uint16_t _color;
        
};