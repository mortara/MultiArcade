#include "cannon_game.hpp"

CannonGame::CannonGame(TFT_eSPI* screen, RotaryEncoder *player1paddle, RotaryEncoder *player2paddle) : Game(screen)
{
    _rotary = player1paddle;
    _lastrotarycount = _rotary->GetCounter();

    _rotary2 = player2paddle;
    _lastrotarycount2 = _rotary2->GetCounter();

    _world = new GameWorld(screen);

    Serial.print("Cannon initialized!");

    delay(100);
}

void CannonGame::Loop()
{
    long time = millis();
    double elapsed = (double)(time - _lastLoop) / 1000.0;
  
    _world->Loop(elapsed);

    if(GameStage == 0)
    {
        _tft->drawString("CANNON", ScreenWidth / 2 - 30, ScreenHeight / 2 - 10, 1);
        if(_rotary->Switch1Pressed || _rotary->Switch2Pressed || _rotary2->Switch1Pressed || _rotary2->Switch2Pressed)
        {
            _tft->fillScreen(DEFAULT_BG_COLOR);
            score = 0;
            
            GameStage = 1;
            StartLevel(1);
            delay(300);
        }
    }
    if(GameStage == 1 || GameStage == 2)
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

        if(GameStage == 2)
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

    if(GameStage == 4)
    {
        _tft->drawString("GAME OVER", ScreenWidth / 2 - 30, ScreenHeight / 2 - 10, 1);
        if(_rotary->Switch1Pressed || _rotary->Switch2Pressed)
        {
            _tft->fillScreen(DEFAULT_BG_COLOR);
            delay(300);
            GameStage = 0;
        }
    }

    _lastLoop = time;

    //_tft.drawString("ball: " + String(_ball->Position.X) + ", " + String(_ball->Position.Y) + " ", 10, 10 , 2);
}

void CannonGame::HUD()
{
    int left = ScreenWidth - 70;

    float altitude = _cannon->Power();
    _tft->drawString("Power:" + String(altitude,1) + "m ", left, 5, 1);

    float angle = _cannon->GetOrientation() - 180;
    _tft->drawString("Ang:" + String((int)angle)+ "  ", left, 15, 1);
}

void CannonGame::scores()
{
    _tft->drawString("Lvl:" + String(level) + " Score:" + String(score) + " Shots:" + String(shots) , 5, 1 , 1);
}

void CannonGame::StartLevel(int l)
{
    _tft->fillScreen(DEFAULT_BG_COLOR);
    _world->Clear();
    _world->SetGravity(Vector2DF(0, 10));

    _ground = new CannonGround(l, 50, _tft->width(), _tft->height());
    _ground->Render(_tft, true);

    _cannon = new Cannon(_rotary, _rotary2, _buzz);
    _cannon->Position = Vector2DF(_ground->CannonPlatformLocation.X, _ground->CannonPlatformLocation.Y);
    _cannon->SetOrientation(45);

    _target = new Target(TFT_RED);
    _target->Position = Vector2DF(_ground->TargetPlatformLocation.X, _ground->TargetPlatformLocation.Y);

    _world->AddObject(_target);
    _world->AddObject(_cannon);

    shots = 3;
}