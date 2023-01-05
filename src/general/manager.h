#include <Arduino.h>
#include "../Input/joystick.h"
#include <TFT_eSPI.h>
#include <SPI.h>
#include "menu.h"
#include "config.h"

class Manager
{
    private:
        Joystick _stick;
        Menu _menu;
        TFT_eSPI _screen;

    public:
        int16_t CurrentGame;

        void Setup();
        void Loop();
        
};