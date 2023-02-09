#include "lunarlander_game.hpp"

LunarLanderGame::LunarLanderGame(TFT_eSPI* screen, RotaryEncoder *player1paddle) : Game(screen)
{
    _rotary = player1paddle;
    
    _world = new GameWorld(screen);
    _world->SetGravity(Vector2DF(0,5));

    Serial.print("LunarLander initialized!");
}

void LunarLanderGame::StartLevel(int l)
{
    _tft->fillScreen(DEFAULT_BG_COLOR);
    _world->Clear();

    _ship = new Capsule(_rotary);
    _ship->Acceleration = Vector2DF(0,0);
    _ship->Velocity = Vector2DF(0,0);
    _ship->Position = Vector2DF(random(_tft->width()), 10);
    _ship->SetOrientation(180);

    _world->AddObject(_ship);
}

void LunarLanderGame::Loop()
{
    long time = millis();
    double elapsed = (double)(time - _lastLoop) / 1000.0;
    _lastLoop = time;
    _world->Loop(elapsed);

    if(GameStage == 0)
    {
        _tft->drawString("LUNAR LANDER", ScreenWidth / 2 - 40, ScreenHeight / 2 - 10, 1);
        if(_rotary->Switch1Pressed || _rotary->Switch2Pressed)
        {           
            GameStage = 1;
            
            StartLevel(1);
            delay(500);
        }
    } else if(GameStage == 1)
    {
        _ship->Control();

    } else if(GameStage == 2)
    {
        _tft->drawString("GAME OVER", ScreenWidth / 2 - 30, ScreenHeight / 2 - 10, 1);
        if(_rotary->Switch1Pressed || _rotary->Switch2Pressed)
        {
            _tft->fillScreen(DEFAULT_BG_COLOR);
            delay(500);
            GameStage = 0;
        }
    } else if(GameStage == 3)
    {
        _stagetimer -= elapsed;
        if(_stagetimer <= 0)
        {
            StartLevel(_level);
            GameStage = 1;
        }
    }
}