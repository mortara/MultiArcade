#include "space_invaders_game.hpp"

void SpaceInvadersGame::Setup(TFT_eSPI screen, RotaryEncoder *player1paddle)
{
    _tft = screen;
    _tft.fillScreen(BLACK);

    _rotary = player1paddle;

    _ship = new Player();
    _ship->Setup(_rotary, screen);

    Serial.print("SpaceInvaders initialized!");
}

void SpaceInvadersGame::scores()
{
    _tft.drawString("Lvl: " + String(level) + " Score: " + String(score) + " Lives: " + String(lives), 1, 1 , 1);
}

void SpaceInvadersGame::StartLevel(int l)
{
    int cols = 8;
    level = l;
    _objects.clear();
    for(int r = 0; r < l + 3; r++)
        for(int c = 0; c < cols; c++)
        {
            Alien *alien = new Alien();
            alien->Setup(c,r,cols, _tft);
            _objects.push_back(alien);
        }
}

void SpaceInvadersGame::ProcessShip(float elapsed)
{
    bool fire = _ship->Control();
    _ship->Render(_tft);
    _ship->OutOfBoundsCheck(_tft);
    _lastshot += elapsed;
    GameObject *shipcoll = CollisionCheck(_ship, 2);
    if(shipcoll != NULL)
    {
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
        Beam *bullet = new Beam();
        bullet->Setup(_ship);
        _objects.push_back(bullet);
        _lastshot = 0;
    }
}

void SpaceInvadersGame::ProcessObjects(float elapsed)
{
    std::list<GameObject *> _removedobjects;
    for (GameObject *obj : _objects)
    {
        obj->Move(elapsed);
        obj->OutOfBoundsCheck(_tft);
        obj->Render(_tft);      
        if(obj->Delete == true)
            _removedobjects.push_back(obj);

        if(obj->ObjectType == 2)
        {
            GameObject *coll = CollisionCheck(obj, 3);
            if(coll != NULL)
            {
                _removedobjects.push_back(coll);
                _removedobjects.push_back(obj);
                score += 5;
            }
        }
    }

    for (GameObject *obj : _removedobjects)
    {
        obj->RemoveFromScreen(_tft);
        _objects.remove(obj);
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
        ProcessShip(elapsed);
        ProcessObjects(elapsed);

        int aliensleft = 0;
        for (GameObject *obj : _objects)
        {
            if(obj->ObjectType == 2)
                aliensleft++;
        }

        if(aliensleft == 0)
        {
            score += level * 5;
            StartLevel(level + 1);
        }

        scores();
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

GameObject* SpaceInvadersGame::CollisionCheck(GameObject *go, int objecttype)
{
    for (GameObject *obj : _objects)
    {
        if(obj->ObjectType != objecttype)
            continue;

        if(go->CollidesWith(obj))
            return obj;
    }

    return NULL;
}