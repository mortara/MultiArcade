#include <Arduino.h>
#include <String.h>
#include <TFT_eSPI.h>
#include "../general/config.h"
#include "../Input/rotary_encoder.hpp"

class Menu
{
    private:
        bool _firsttime = true;
        int16_t _currentIndex = 0;
        int16_t _lastCounter = 0;
        TFT_eSPI* _tft;
        RotaryEncoder *_player1paddle;

        int16_t _gamecount = 5;
        String _items[5] = { "Asteroids", "1 Player Pong", "2 Player Pong","Breakout", "Space Invaders" };

    public:
        Menu(TFT_eSPI* screen, RotaryEncoder *player1);

        int Loop();

};