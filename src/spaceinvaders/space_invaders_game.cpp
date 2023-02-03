#include "space_invaders_game.hpp"

SpaceInvadersGame::SpaceInvadersGame(TFT_eSPI* screen, RotaryEncoder *player1paddle) : Game(screen)
{
    _tft->fillScreen(DEFAULT_BG_COLOR);

    _rotary = player1paddle;
    
    _world = new GameWorld(screen);
    _ship = new Player(_rotary, screen);

    _lastLoop = millis();

    Serial.print("SpaceInvaders initialized!");
}

void SpaceInvadersGame::scores()
{
    _tft->drawString("Lvl: " + String(level) + " Score: " + String(score) + " Lives: " + String(lives), 1, 1 , 1);
}

void SpaceInvadersGame::StartLevel(int l)
{
    _tft->fillScreen(DEFAULT_BG_COLOR);

    int cols = _maxcols;
    level = l;
    int rows = l + 3;
    if(rows > _maxrows)
        rows = _maxrows;

    _world->DeleteObjects();
    
    for(int r = 0; r < rows; r++)
        for(int c = 0; c < cols; c++)
        {
            Alien *alien = new Alien(c,r,cols, _tft);
            _world->AddObject(alien);         
        }
}

void SpaceInvadersGame::ProcessShip(float elapsed)
{
    bool fire = _ship->Control();
    _ship->Render(_tft);
    _ship->OutOfBoundsCheck(_tft);
    _lastshot += elapsed;

    GameObject *shipcoll = _world->CollisionCheck(_ship, 2);
    if(shipcoll == NULL)
        shipcoll = _world->CollisionCheck(_ship, 3);

    if(shipcoll != NULL)
    {
        shipcoll->Delete = true;
        _buzz->PlayNoise(150);
        lives--;
        if(lives == 0)
        {
            GameStage = 2;
            return;
        }
        else
        {
            stagetimer = 3;
            GameStage = 3;
            return;
        }
    } else if(fire && _lastshot >= _reloadtime)
    {
        Beam *bullet = new Beam(_ship);
        _world->AddObject(bullet);
        _buzz->PlayTone(600, 50);
        _lastshot = 0;
    }
}

void SpaceInvadersGame::ProcessObjects(float elapsed)
{
    _lastalienshot += elapsed;
    std::list<GameObject *>* _objects = _world->GetObjects();
    for (GameObject *obj : *_objects)
    {
        if(obj->Delete == true)
            continue;

        if(obj->ObjectType == 2)
        {
            Alien* alien = static_cast<Alien*>(obj);
            GameObject *coll = _world->CollisionCheck(obj, 3);
            if(coll != NULL)
            {
                coll->Delete = true;
                obj->Delete = true;
                score += 5;
                _buzz->PlayNoise(150);
            } 
            else if(GameStage != 3)
            {
                // Sometimes Aliens fire back
                if(random(1000) < _lastalienshot)
                {
                    bool blocked = false;
                    for (GameObject *obj_test : *_objects)
                    {
                        if(obj_test->Delete || obj_test->ObjectType != 2 || obj == obj_test)
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
                        Beam *bullet = new Beam(alien);
                        _world->AddObject(bullet);
                        _lastalienshot = 0;
                        _buzz->PlayTone(400, 50);
                    }
                    
                }
            }
        }
    }
}

void SpaceInvadersGame::Loop()
{
    long time = millis();
    double elapsed = (double)(time - _lastLoop) / 1000.0;
    _lastLoop = time;
    _world->Loop(elapsed);

    if(GameStage == 0)
    {
        _tft->drawString("SPACE INVADERS", ScreenWidth / 2 - 40, ScreenHeight / 2 - 10, 1);
        if(_rotary->Switch1Pressed || _rotary->Switch2Pressed)
        {           
            score = 0;
            GameStage = 1;
            lives = 3;
            
            StartLevel(1);
            delay(500);
        }
    } else if(GameStage == 1)
    {
        ProcessShip(elapsed);
        ProcessObjects(elapsed);

        int aliensleft = _world->CountObjects(2);

        if(aliensleft == 0)
        {
            score += level * 5;
            StartLevel(level + 1);
        }

        scores();
    } else if(GameStage == 2)
    {
        ProcessObjects(elapsed);
        scores();
        _tft->drawString("GAME OVER", ScreenWidth / 2 - 30, ScreenHeight / 2 - 10, 1);
        if(_rotary->Switch1Pressed || _rotary->Switch2Pressed)
        {
            _tft->fillScreen(DEFAULT_BG_COLOR);
            delay(500);
            GameStage = 0;
        }
    } else if(GameStage == 3)
    {
        ProcessObjects(elapsed);
        scores();
        stagetimer -= elapsed;
        if(stagetimer <= 0)
        {
            StartLevel(level);
            GameStage = 1;
        }
    }

    //_tft.drawString("ShipPos: " + String(_ship->X) + ", " + String(_ship->Y) + " ", 10, 10 , 2);
}