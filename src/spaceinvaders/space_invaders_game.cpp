#include "space_invaders_game.hpp"

void SpaceInvadersGame::Setup(TFT_eSPI* screen, RotaryEncoder *player1paddle)
{
    _tft = screen;
    _tft->fillScreen(BLACK);

    _rotary = player1paddle;

    _buzz = Buzzer();
    _buzz.Setup();
    
    _ship = new Player();
    _ship->Setup(_rotary, screen);

    Serial.print("SpaceInvaders initialized!");
}

void SpaceInvadersGame::scores()
{
    _tft->drawString("Lvl: " + String(level) + " Score: " + String(score) + " Lives: " + String(lives), 1, 1 , 1);
}

void SpaceInvadersGame::StartLevel(int l)
{
    _tft->fillScreen(BLACK);

    int cols = _maxcols;
    level = l;
    int rows = l + 3;
    if(rows > _maxrows)
        rows = _maxrows;

    for (GameObject *obj : _objects)
        delete obj;

    _objects.clear();
    
    for(int r = 0; r < rows; r++)
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
    if(shipcoll == NULL)
        shipcoll = CollisionCheck(_ship, 3);

    if(shipcoll != NULL)
    {
        shipcoll->Delete = true;
        _buzz.PlayNoise(150);
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
    } else if(fire && _lastshot >= _reloadtime)
    {
        Beam *bullet = new Beam();
        bullet->Setup(_ship);
        _objects.push_back(bullet);
        _buzz.PlayTone(600, 50);
        _lastshot = 0;
    }
}

void SpaceInvadersGame::ProcessObjects(float elapsed)
{
    _lastalienshot += elapsed;
    
    for (GameObject *obj : _objects)
    {
        if(obj->Delete == true)
            continue;

        obj->Move(elapsed);
        if(obj->OutOfBoundsCheck(_tft))
        {
            obj->Delete = true;
            continue;
        }

        obj->Render(_tft);      
        
        if(obj->ObjectType == 2)
        {
            Alien* alien = static_cast<Alien*>(obj);
            GameObject *coll = CollisionCheck(obj, 3);
            if(coll != NULL)
            {
                coll->Delete = true;
                obj->Delete = true;
                score += 5;
                _buzz.PlayNoise(150);
            } else if(gamestage != 3)
            {
                // Sometimes Aliens fire back
                if(random(1000) < _lastalienshot)
                {
                    bool blocked = false;
                    for (GameObject *obj_test : _objects)
                    {
                        if(obj_test->Delete || obj_test->ObjectType != 2)
                            continue;
                        
                        Alien* alien2 = static_cast<Alien*>(obj_test);
                        if(alien2->Column == alien->Column && alien2->Row > alien->Row)
                        {
                            blocked = true;
                            break;
                        }
                    }

                    if(!blocked && random(10) > 8)
                    {
                        Beam *bullet = new Beam();
                        bullet->Setup(alien);
                        _objects.push_back(bullet);
                        _lastalienshot = 0;
                        _buzz.PlayTone(400, 50);
                    }
                    
                }
            }
        }
    }

    std::list<GameObject *> _removedobjects;
    for (GameObject *obj : _objects)
    {
        if(obj->Delete == true)
            _removedobjects.push_back(obj);
    }
  
    for (GameObject *obj : _removedobjects)
    {
        obj->RemoveFromScreen(_tft);
        _objects.remove(obj);
        delete obj;
    }
}

void SpaceInvadersGame::Loop()
{
    long time = millis();
    double elapsed = (double)(time - _lastLoop) / 1000.0;
  
    if(gamestage == 0)
    {
        _tft->drawString("SPACE INVADERS", _tft->width() / 2 - 40, _tft->height() / 2 - 10, 1);
        if(_rotary->Switch1Pressed || _rotary->Switch2Pressed)
        {
            _tft->fillScreen(BLACK);
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

        int aliensleft = std::count_if(_objects.begin(), _objects.end(), [](GameObject *go) { return go->ObjectType == 2; });

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
        _tft->drawString("GAME OVER", _tft->width() / 2 - 30, _tft->height() / 2 - 10, 1);
        if(_rotary->Switch1Pressed || _rotary->Switch2Pressed)
        {
            _tft->fillScreen(BLACK);
            delay(500);
            gamestage = 0;
        }
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
    }

    _lastLoop = time;
    _firstloop = false;

    //_tft.drawString("ShipPos: " + String(_ship->X) + ", " + String(_ship->Y) + " ", 10, 10 , 2);
}

GameObject* SpaceInvadersGame::CollisionCheck(GameObject *go, int objecttype)
{
    for (GameObject *obj : _objects)
    {
        if(obj->Delete || obj->ObjectType != objecttype)
            continue;

        if(go->CollidesWith(obj))
            return obj;
    }

    return NULL;
}