#include <Arduino.h>
#include <String.h>
#include <TFT_eSPI.h>
#include "../general/config.h"
#include "../Input/rotary_encoder.h"

class Menu
{
    private:
        bool _firsttime = true;
        int _currentIndex;
        int _lastCounter = 0;
        TFT_eSPI _tft;
        RotaryEncoder *_player1paddle;

        int _gamecount = 4;
        String _items[4] = { "Asteroids", "1 Player Pong","Breakout", "Space Invaders" };

    public:
        void Setup(TFT_eSPI screen, RotaryEncoder *player1);

        int Loop();

};