#include "screen.h"

void Screen::Setup()
{
    tft = TFT_eSPI();

    Width = 128;
    Height = 160;

    tft.init();

    tft.setRotation(1);

    tft.fillScreen(BLACK);
  
    tft.setTextColor(WHITE, BLACK);
}

void Screen::Clear()
{

}

void Screen::setTextColor(u_int16_t color)
{
    tft.setTextColor(color);
}