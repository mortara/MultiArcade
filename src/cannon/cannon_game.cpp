#include "cannon_game.hpp"

CannonGame::CannonGame(TFT_eSPI* screen, RotaryEncoder *player1paddle) : Game(screen)
{
    _rotary = player1paddle;
    _lastrotarycount = _rotary->GetCounter();

    _world = new GameWorld(screen);

    Serial.print("Cannon initialized!");

    delay(100);
}

void CannonGame::Loop()
{
    long time = millis();
    float elapsed = (float)(time - _lastLoop) / 1000.0f;
    _lastLoop = time;
    _world->Loop(elapsed);

    if(GameStage == 0)
    {
        _tft->drawString("CANNON", ScreenWidth / 2 - 30, ScreenHeight / 2 - 10, 1);
        if(_rotary->Switch1Pressed || _rotary->Switch2Pressed)
        {
            
            score = 0;
            
            GameStage = 1;
            StartLevel(1);
            delay(300);
        }
    }
    else if(GameStage == 1 || GameStage == 2)
    {
        scores();
        HUD();

        if(GameStage == 1)
        {
            bool fire = _cannon->Control();

            if(fire && shots > 0)
            {
                _cannonball = new CannonBall(_cannon, _cannon->Power());
                _world->AddObject(_cannonball);
                GameStage = 2;
                _buzz->PlayTone(100, 50);
                shots--;
            }
        }
        else if(GameStage == 2)
        {
            GameObject *coll = _world->CollisionCheck(_cannonball, 2);
            if(coll == _target)
            {
                coll->Delete = true;
                _cannonball->Delete = true;
                score += (shots + 1 + level);
                _world->Explode(_target);
                _buzz->PlayNoise(300);
                GameStage = 3;
            }
            else if(_cannonball->CollidesWith(_ground))
            {
                _cannonball->Delete = true;
                _buzz->PlayNoise(300);

                if(shots == 0)
                {
                    GameStage = 4;
                }
                else
                {
                    GameStage = 1;
                }
            }
        }
    }
    else if(GameStage == 3)
    {
        _stagetimer -= elapsed;
        _tft->drawString("HIT!", ScreenWidth / 2 - 25, ScreenHeight / 2 - 20, 1);
        _tft->drawString("Next level in " + String(_stagetimer,1) + "s ", ScreenWidth / 2 - 55, ScreenHeight / 2 - 10, 1);
        if(_stagetimer <= 0)
        {
            StartLevel(level+1);
            GameStage = 1;
        }
    }
    else if(GameStage == 4)
    {
        _tft->drawString("GAME OVER", ScreenWidth / 2 - 30, ScreenHeight / 2 - 10, 1);
        if(_rotary->Switch1Pressed || _rotary->Switch2Pressed)
        {
            _tft->fillScreen(DEFAULT_BG_COLOR);
            delay(300);
            GameStage = 0;
        }
    } 
    //_tft.drawString("ball: " + String(_ball->Position.X) + ", " + String(_ball->Position.Y) + " ", 10, 10 , 2);
}

void CannonGame::HUD()
{
    int left = ScreenWidth - 70;

    float altitude = _cannon->Power();
    if(_cannon->Inputmode != 1)
        _tft->setTextColor(DEFAULT_TEXT_COLOR, DEFAULT_BG_COLOR, true);
    else
        _tft->setTextColor(TFT_RED, DEFAULT_BG_COLOR, true);
    _tft->drawString("Power:" + String(altitude,1) + "% ", left, 10, 1);

    float angle = _cannon->GetOrientation() - 180;
    if(_cannon->Inputmode != 0)
        _tft->setTextColor(DEFAULT_TEXT_COLOR, DEFAULT_BG_COLOR, true);
    else
        _tft->setTextColor(TFT_RED, DEFAULT_BG_COLOR, true);
    _tft->drawString("Angle:" + String((int)angle)+ "  ", left, 20, 1);
}

void CannonGame::scores()
{
    _tft->setTextColor(DEFAULT_TEXT_COLOR, DEFAULT_BG_COLOR, true);
    _tft->drawString("Lvl:" + String(level) + " Score:" + String(score) + " Shots:" + String(shots) , 5, 1 , 1);
}

void CannonGame::StartLevel(int l)
{
    _tft->fillScreen(DEFAULT_BG_COLOR);
    _world->Clear();
    _world->SetGravity(Vector2DF(0, 10));
    _world->SetDrag(0.7f);


    if(_ground != nullptr)
        delete _ground;

    _ground = new CannonGround(l+3, 50, _tft->width(), _tft->height());
    _ground->Render(_tft, true);

    _cannon = new Cannon(_rotary, _buzz);
    _cannon->Position = Vector2DF(_ground->CannonPlatformLocation.X, _ground->CannonPlatformLocation.Y);
    _cannon->Acceleration = Vector2DF(0,0);
    _cannon->Velocity = Vector2DF(0,0);
    _cannon->SetOrientation(0);
    _cannon->Gravity = false;
    _world->AddObject(_cannon);

    _target = new Target(TFT_RED);
    _target->Position = Vector2DF(_ground->TargetPlatformLocation.X, _ground->TargetPlatformLocation.Y -5);
    _target->Size = Vector2DF(5, 5);
    _target->Acceleration = Vector2DF(0,0);
    _target->Velocity = Vector2DF(0,0);
    _target->Gravity = false;
    _world->AddObject(_target);
    

    shots = 3;
}