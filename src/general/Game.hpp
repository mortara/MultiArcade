#include <Arduino.h>
#include <TFT_eSPI.h>
#include "../sound/sound.hpp"

#ifndef GAME_H
#define GAME_H

class Game
{
    protected:

        TFT_eSPI* _tft;
        Buzzer* _buzz;

    public:

        Game(TFT_eSPI* _screen)
        {
            ScreenWidth = _screen->width();
            ScreenHeight = _screen->height();

            _tft = _screen;

            _buzz = new Buzzer();
            _buzz->Setup();
        }

        int16_t ScreenWidth;
        int16_t ScreenHeight;
        int16_t GameStage;

    
};

#endif