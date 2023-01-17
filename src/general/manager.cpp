#include "manager.hpp"

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
    _rotary->Setup(CLK1_PIN, DT1_PIN, SW1_PIN, SW1_PIN2, true);

    _rotary2 = new RotaryEncoder();
    _rotary2->Setup(CLK2_PIN, DT2_PIN, SW2_PIN, SW2_PIN2, false);

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

    if(CurrentGame == 3)
    {
        _rotary2->Loop();
    }

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
                case 2:

                    CurrentGame = 3;
                    _pong = Pong();
                    _pong.Setup(_screen, _rotary, _rotary2);
                    break;
                case 3:
                    CurrentGame = 4;
                    _breakout = BreakoutGame();
                    _breakout.Setup(_screen, _rotary, Width, Height);
                    break;
                case 4:
                    CurrentGame = 5;
                    _spaceInvaders = SpaceInvadersGame();
                    _spaceInvaders.Setup(_screen, _rotary, Width, Height);
                    break;
            }
        }
        return;
    }

    if(CurrentGame == 1)
    {
        _asteroids.Loop();
    }
    if(CurrentGame == 2 || CurrentGame == 3)
    {
        _pong.Loop();
    }
    if(CurrentGame == 4)
    {
        _breakout.Loop();
    }
    if(CurrentGame == 5)
    {
        _spaceInvaders.Loop();
    }
}