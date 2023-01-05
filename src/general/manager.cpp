#include "manager.h"

void Manager::Setup()
{
    randomSeed(analogRead(0)*analogRead(1));

    CurrentGame = 0;
    _stick = Joystick();
    _stick.Setup();

    _menu = Menu();
    _menu.Setup();

    _screen = TFT_eSPI();
    
   
    _screen.init();

    _screen.setRotation(1);

    _screen.fillScreen(BLACK);
    
    _screen.setTextColor(WHITE, BLACK);
}

void Manager::Loop()
{
    _stick.Loop();

    _screen.drawString("X: " + String(_stick.X) + ", Y: " + String(_stick.Y) + ", SW: " + String(_stick.SW), 10, 0 , 2);

    if(CurrentGame == 0)
    {
        _menu.Render(_screen);
    }
}