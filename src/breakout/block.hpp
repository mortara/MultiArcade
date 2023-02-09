#include <Arduino.h>
#include "../general/gameobject.hpp"

class Block : public GameObject
{
    public:
        Block(uint16_t color);
        void Render(TFT_eSPI* screen, bool force = false) override;
        void RemoveFromScreen(TFT_eSPI* screen) override;

    private:
        uint16_t _color;      
};