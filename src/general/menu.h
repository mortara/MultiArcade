#include <Arduino.h>
#include <String.h>
#include <TFT_eSPI.h>
#include "config.h"

class Menu
{
    private:
        int _currentIndex;

        String _items[4] = { "Asteroids", "Pong","Breakout", "Space Invaders" };

    public:
        void Setup();

        void Render(TFT_eSPI screen);

        void MoveSelection(int i);
};