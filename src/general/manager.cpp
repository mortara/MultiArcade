#include "manager.h"

TFT_eSPI Manager::Setup()
{
    Serial.begin(115200);

    randomSeed(analogRead(0)*analogRead(1));

    CurrentGame = 0;

    Width = 160;
    Height = 128;

    //_stick = Joystick();
    //_stick.Setup();

    _rotary = new RotaryEncoder();
    _rotary->Setup();

    _screen = TFT_eSPI();
    _screen.init();
    _screen.setRotation(1);
    _screen.fillScreen(BLACK);
    _screen.setTextColor(WHITE, BLACK);

    _menu = Menu();
    _menu.Setup(_screen, _rotary);

    return _screen;
}

void Manager::Loop()
{
    

    //_stick.Loop();
    _rotary->Loop();

    //_screen.drawString("X: " + String(_stick.X) + ", Y: " + String(_stick.Y) + ", SW: " + String(_stick.SW), 10, 0 , 2);

    if(CurrentGame == 0)
    {
        int newgame = _menu.Loop();
        if(newgame >= 0)
        {
            switch(newgame)
            {
                case 0:
                    CurrentGame = 1;
                    _asteroids = AsteroidsGame();
                    _asteroids.Setup(_screen, _rotary, Width, Height);
                    break;
                case 1:
                    CurrentGame = 2;
                    _pong = Pong();
                    _pong.Setup(_screen, _rotary);
                    break;
            }
        }
    }

    if(CurrentGame == 1)
    {
        _asteroids.Loop();
    }
    if(CurrentGame == 2)
    {
        _pong.Loop();
    }

}