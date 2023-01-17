#include "menu.hpp"
#include "../general/config.h"

void Menu::Setup(TFT_eSPI screen, RotaryEncoder *p1)
{
    _tft = screen;
    _player1paddle = p1;
}

int Menu::Loop()
{
    int16_t cm = 0;
    int16_t cc = _player1paddle->Counter;
   
    if(_lastCounter != cc)
    {
        if(cc > _lastCounter)
            cm = 1;
        else
            cm = -1;

        //_screen.drawString("Counter: " + String(cc) + ", SW: " + String(_rotary->SW), 10, 100 , 2);

        _lastCounter = cc;

    }

    if(cm != 0 || _firsttime) 
    {
        _currentIndex += cm;
        if(_currentIndex > (_gamecount-1))
            _currentIndex = 0;

        if(_currentIndex < 0)
            _currentIndex = (_gamecount-1);

        for(int i = 0; i < _gamecount; i++)
        {
            if(i == _currentIndex)
                _tft.setTextColor(TFT_BLUE);
            else
                _tft.setTextColor(WHITE);

            _tft.drawString(_items[i], 20, 20 + i * 12 , 2);
        }
        _firsttime = false;
        delay(50);
    }

    if(_player1paddle->Switch1Pressed || _player1paddle->Switch2Pressed)
        return _currentIndex;

    return -1;
}
