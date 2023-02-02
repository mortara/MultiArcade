#include "block.hpp"


Block::Block(uint16_t color)
{
    _color = color;
}

void Block::Render(TFT_eSPI* screen)
{
    screen->fillRect((int)Position.X, (int)Position.Y, (int)Size.X, (int)Size.Y, _color);
}

void Block::RemoveFromScreen(TFT_eSPI* screen)
{
    screen->fillRect((int)Position.X, (int)Position.Y, (int)Size.X, (int)Size.Y, BLACK);
}
