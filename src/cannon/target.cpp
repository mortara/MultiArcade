#include "target.hpp"

Target::Target(uint16_t color)
{
    ObjectType = 2;
    _color = color;
}

void Target::Render(TFT_eSPI* screen, bool force)
{
    screen->fillRect((int)Position.X, (int)Position.Y, (int)Size.X, (int)Size.Y, _color);
}

void Target::RemoveFromScreen(TFT_eSPI* screen)
{
    screen->fillRect((int)Position.X, (int)Position.Y, (int)Size.X, (int)Size.Y, BLACK);
}