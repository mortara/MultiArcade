#include "lunarlander_game.hpp"

LunarLanderGame::LunarLanderGame(TFT_eSPI* screen, RotaryEncoder *player1paddle) : Game(screen)
{
    _rotary = player1paddle;
    
    _world = new GameWorld(screen);
    

    Serial.print("LunarLander initialized!");
}

void LunarLanderGame::StartLevel(int l)
{
    _tft->fillScreen(DEFAULT_BG_COLOR);
    _world->Clear();
    _world->SetGravity(Vector2DF(0, 2 + l));

    _ground = new Ground(10, _tft->width(), _tft->height());
    _ground->Render(_tft, true);

    _ship = new Capsule(_rotary, _buzz);
    _ship->Acceleration = Vector2DF(0,0);
    _ship->Velocity = Vector2DF(0,0);
    _ship->Position = Vector2DF(random(_tft->width() - 30) + 15, 20);
    _ship->SetOrientation(180);

    _world->AddObject(_ship);
}

void LunarLanderGame::HUD()
{
    int left = ScreenWidth - 70;

    float fuelp = (_ship->Fuel / _ship->FuelMax) * 100.0;
    if(fuelp > 10)
        _tft->setTextColor(DEFAULT_TEXT_COLOR, DEFAULT_BG_COLOR, true);
    else
        _tft->setTextColor(TFT_RED, DEFAULT_BG_COLOR, true);
    _tft->drawString("Fuel :" + String((int)fuelp) + "% ", 5, 5, 1);

    float speed = _ship->Speed();
    if(speed < 5)
        _tft->setTextColor(DEFAULT_TEXT_COLOR, DEFAULT_BG_COLOR, true);
    else
        _tft->setTextColor(TFT_RED, DEFAULT_BG_COLOR, true);

    _tft->drawString("Speed:" + String(speed,1) + "m/s ", 5, 15, 1);

    float altitude = _ship->Altitude(_ground);
    if(altitude > 10)
        _tft->setTextColor(DEFAULT_TEXT_COLOR, DEFAULT_BG_COLOR, true);
    else
        _tft->setTextColor(TFT_RED, DEFAULT_BG_COLOR, true);
    _tft->drawString("Alt:" + String(altitude,1) + "m ", left, 5, 1);

    float angle = _ship->GetOrientation() - 180;
    if(abs(angle) < 5)
        _tft->setTextColor(DEFAULT_TEXT_COLOR, DEFAULT_BG_COLOR, true);
    else
        _tft->setTextColor(TFT_RED, DEFAULT_BG_COLOR, true);
    _tft->drawString("Ang:" + String((int)angle)+ "  ", left, 15, 1);
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
        HUD();

        if(_ship->CollidesWith(_ground))
        {
            if(_ship->Speed() < 5 && abs(180 - _ship->GetOrientation()) < 5)
            {
                _ship->Velocity = Vector2DF(0,0);
                _ship->Gravity = false;
                _level++;
                GameStage = 3;
            }
            else
            {
                _world->Explode(_ship);
                _buzz->PlayNoise(1000);
                _ship->Visible = false; 
                GameStage = 2;
                _stagetimer = 5;
            }
        }

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
        _tft->drawString("LANDED!", ScreenWidth / 2 - 25, ScreenHeight / 2 - 20, 1);
        _tft->drawString("Next level in " + String(_stagetimer,1) + "s ", ScreenWidth / 2 - 55, ScreenHeight / 2 - 10, 1);
        if(_stagetimer <= 0)
        {
            StartLevel(_level);
            GameStage = 1;
        }
    }
}