#include "menu.h"


void Menu::Setup(int _num)
{
    _numItems = _num;
    _items = new String[_num];
}

void Menu::AddItem(int index, String item)
{
    _items[index] = item;
}

void Menu::Render(Screen screen)
{
    for(int i = 0; i < _numItems; i++)
    {
        if(i == _currentIndex)
            tft.setTextColor(WHITE);
        else
            tft.setTextColor(BLUE);

        tft.drawString(_items[i], 20, 20 + i * 10 , 2);
    }
}

void Menu::MoveSelection(int i)
{
    _currentIndex = i;
}