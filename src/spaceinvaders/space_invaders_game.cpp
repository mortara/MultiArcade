#include "space_invaders_game.h"

void SpaceInvadersGame::Setup(TFT_eSPI screen, RotaryEncoder *player1paddle, int16_t screen_height, int16_t screen_width)
{
    h = screen_width;
    w = screen_height;

    _tft = screen;
    _tft.fillScreen(BLACK);

    _rotary = player1paddle;

    
    Serial.print("SpaceInvaders initialized!");
}

void SpaceInvadersGame::scores()
{
    _tft.drawString("Level: " + String(level) + "   Score: " + String(score) , 10, 2 , 2);
    
}

void SpaceInvadersGame::Loop()
{
    long time = millis();
    double elapsed = (double)(time - _lastLoop) / 1000.0;
  
    scores();

    _lastLoop = time;

    //_tft.drawString("ShipPos: " + String(_ship->X) + ", " + String(_ship->Y) + " ", 10, 10 , 2);
}