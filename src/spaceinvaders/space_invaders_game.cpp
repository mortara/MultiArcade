#include "space_invaders_game.hpp"

void SpaceInvadersGame::Setup(TFT_eSPI screen, RotaryEncoder *player1paddle)
{
    _tft = screen;
    _tft.fillScreen(BLACK);

    _rotary = player1paddle;

    Serial.print("SpaceInvaders initialized!");
}

void SpaceInvadersGame::scores()
{
    _tft.drawString("Level: " + String(level) + "   Score: " + String(score) , 10, 2 , 2);
    
}

void SpaceInvadersGame::ProcessShip(float elapsed)
{
    bool fire = _ship->Control();
    _ship->Move(elapsed);
    _ship->Render(_tft);

    OutOfBoundsCheck(_ship);
    GameObject *shipcoll = CollisionCheck(_ship, 2);
    if(shipcoll != NULL)
    {
        
        Explode(shipcoll);
        Explode(_ship);
        
        shipcoll->Delete = true;

        lives--;
        if(lives == 0)
        {
            gamestage = 2;
            return;
        }
        else
        {
            stagetimer = 3;
            gamestage = 3;
            return;
        }
    }

    if(fire && _lastshot >= _reloadtime)
    {
        Bullet *bullet = new Bullet();
        bullet->Setup(_ship);
        _objects.push_back(bullet);
        _lastshot = 0;
    }
}

void SpaceInvadersGame::ProcessObjects(float elapsed)
{
    std::list<GameObject *> _removedobjects;
    for (Alien *obj : _aliens)
    {
        obj->Move(elapsed);
        obj->Render(_tft);      
        if(obj->Delete == true)
            _removedobjects.push_back(obj);
    }

    for (Alien *obj : _removedobjects)
    {
        obj->RemoveFromScreen(_tft);
        _aliens.remove(obj);
    }
}

void SpaceInvadersGame::Loop()
{
    long time = millis();
    double elapsed = (double)(time - _lastLoop) / 1000.0;
  
    if(gamestage == 0)
    {
        _tft.drawString("SPACE INVADERS", _tft.width() / 2 - 40, _tft.height() / 2 - 10, 1);
        if(_rotary->Switch1Pressed || _rotary->Switch2Pressed)
        {
            _tft.fillScreen(BLACK);
            score = 0;
            gamestage = 1;
            lives = 3;
            
            StartLevel(1);
            delay(500);
        }
    } else if(gamestage == 1)
    {
       
        ProcessObjects(elapsed);

        
        if(_aliens.empty())
        {
            score += level * 5;
            StartLevel(level + 1);
        }

        scores();
    } else if(gamestage == 3)
    {
        ProcessObjects(elapsed);
        scores();
        stagetimer -= elapsed;
        if(stagetimer <= 0)
        {
            StartLevel(level);
            gamestage = 1;
        }
    } else if(gamestage == 2)
    {
        ProcessObjects(elapsed);
        scores();
        _tft.drawString("GAME OVER", _tft.width() / 2 - 30, _tft.height() / 2 - 10, 1);
        if(_rotary->Switch1Pressed || _rotary->Switch2Pressed)
        {
            _tft.fillScreen(BLACK);
            delay(500);
            gamestage = 0;
        }
    }

    _lastLoop = time;
    _firstloop = false;

    //_tft.drawString("ShipPos: " + String(_ship->X) + ", " + String(_ship->Y) + " ", 10, 10 , 2);
}