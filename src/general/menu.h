#include <Arduino.h>
#include <String.h>
#include "../screen/screen.h"

class Menu
{
    private:
        int _numItems;
        int _currentIndex;

        String[] _items;

    public:
        void Setup(int numitems);

        void AddItem(int index, String item);

        void Render(Screen screen);

        void MoveSelection(int i);
};