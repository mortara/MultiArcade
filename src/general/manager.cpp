#include "manager.hpp"

TFT_eSPI* Manager::Setup()
{
    randomSeed(analogRead(0)*analogRead(1));

    CurrentGame = 0;

    //_stick = Joystick();
    //_stick.Setup();

    _rotary = new RotaryEncoder(CLK1_PIN, DT1_PIN, SW1_PIN, SW1_PIN2, true);
    _rotary2 = new RotaryEncoder(CLK2_PIN, DT2_PIN, SW2_PIN, SW2_PIN2, false);
    _screen = new TFT_eSPI();

    _screen->init();
    _screen->setRotation(1);
    _screen->fillScreen(DEFAULT_BG_COLOR);
    _screen->setTextColor(DEFAULT_TEXT_COLOR, DEFAULT_BG_COLOR, true);

    _menu = new Menu(_screen, _rotary);

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
        int newgame = _menu->Loop();
        if(newgame >= 0)
        {
            switch(newgame)
            {
                case 0:
                    CurrentGame = 1;
                    _asteroids = new AsteroidsGame(_screen, _rotary);
                    break;
                case 1:
                    CurrentGame = 2;
                    _pong = new Pong(_screen, _rotary);
                    break;
                case 2:

                    CurrentGame = 3;
                    _pong = new Pong(_screen, _rotary, _rotary2);
                    break;
                case 3:
                    CurrentGame = 4;
                    _breakout = new BreakoutGame(_screen, _rotary);
                    break;
                case 4:
                    CurrentGame = 5;
                    _spaceInvaders = new SpaceInvadersGame(_screen, _rotary);
                    break;
                case 5:
                    CurrentGame = 6;
                    _lunarLander = new LunarLanderGame(_screen, _rotary);
                    break;
            }
        }
        return;
    }

    if(CurrentGame == 1)
    {
        _asteroids->Loop();
    }
    else if(CurrentGame == 2 || CurrentGame == 3)
    {
        _pong->Loop();
    }
    else if(CurrentGame == 4)
    {
        _breakout->Loop();
    }
    else if(CurrentGame == 5)
    {
        _spaceInvaders->Loop();
    }
    else if(CurrentGame == 6)
    {
        _lunarLander->Loop();
    }
}