#include "block.hpp"


void Block::Setup(uint16_t color)
{
    _color = color;
}

void Block::Render(TFT_eSPI screen)
{
    screen.fillRect((int)Position.X, (int)Position.Y, (int)w, (int)h, _color);
}

void Block::RemoveFromScreen(TFT_eSPI screen)
{
    screen.fillRect((int)Position.X, (int)Position.Y, (int)w, (int)h, BLACK);
}
