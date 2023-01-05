#include "menu.h"
#include "config.h"

void Menu::Setup()
{
  
}

void Menu::Render(TFT_eSPI tft)
{
    for(int i = 0; i < 4; i++)
    {
        if(i == _currentIndex)
            tft.setTextColor(BLUE);
        else
            tft.setTextColor(WHITE);

        tft.drawString(_items[i], 20, 20 + i * 12 , 2);
    }
}

void Menu::MoveSelection(int i)
{
    _currentIndex = i;
}