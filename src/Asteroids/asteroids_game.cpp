#include "asteroids_game.hpp"
#include "../general/config.h"

void AsteroidsGame::Setup(TFT_eSPI* screen, RotaryEncoder *player1paddle)
{
 
    _tft = screen;
    _tft->fillScreen(BLACK);

    _rotary = player1paddle;

    _ship = new Ship();
    _ship->Setup(_rotary);

    _buzz = Buzzer();
    _buzz.Setup();
    Serial.print("Asteroids initialized!");
}

void AsteroidsGame::StartLevel(int l)
{
    level = l;
    _firstloop = true;

    _tft->fillScreen(BLACK);

    _ship->Position = Vector2DF(_tft->width()/2,_tft->height()/2);
    _ship->Velocity = Vector2DF(0,0);
    _ship->Render(_tft, true);
    int numa = 3 + l;

    for (GameObject *obj : _objects)
        delete obj;
    
    _objects.clear();

    for(int i = 0; i < numa; i++)
    {
        Asteroid *ast = new Asteroid();
        int sc = 3; // We want Size 3 asteroids

        if(random(50) < (l*3))
            sc = 4;         // but sometimes size 4 ones. the higher the level, the more size 4 asteroids are coming

        ast->Setup(sc, _tft->width(), _tft->height());
        ast->Render(_tft, true);
        _objects.push_back(ast);
    }

}

void AsteroidsGame::scores()
{
    _tft->drawString("Lvl:" + String(level) + " Score:" + String(score) + " Ships:" + String(lives) , 5, 1 , 1);
    
}

void AsteroidsGame::ProcessShip(float elapsed)
{
    bool fire = _ship->Control();
    _ship->Move(elapsed);
    _ship->Render(_tft);

    _ship->OutOfBoundsCheck(_tft);
    GameObject *shipcoll = CollisionCheck(_ship, 2);
    if(shipcoll != NULL)
    {
        
        Explode(shipcoll);
        Explode(_ship);

        _buzz.PlayNoise(350);
        
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

        _buzz.PlayTone(100, 50);
    }
}

void AsteroidsGame::ProcessObjects(float elapsed)
{
    
    for (GameObject *obj : _objects)
    {
        obj->Move(elapsed);
        obj->Render(_tft);      
        if(obj->OutOfBoundsCheck(_tft))
        {
            obj->Delete = true;
            continue;
        }

        else if(obj->ObjectType == 3)
        {
            GameObject *coll = CollisionCheck(obj, 2);
            if(coll != NULL)
            {
                obj->Delete = true;
                coll->Delete = true;

                Asteroid *ast = static_cast<Asteroid *>(coll);
                int s = ast->Sizeclass;
                score+=ast->Sizeclass * 5;
                if(s > 2)
                {
                    for(int i = 0; i < s; i++)
                    {
                        Asteroid *asn = new Asteroid();
                        asn->Setup(s-1, _tft->width(), _tft->height());
                        asn->Position = ast->Position;
                        asn->Velocity = asn->Velocity * (double)1.5;
                        _objects.push_back(asn);
                    }
                    _buzz.PlayNoise(150);
                }
                else
                {
                    Explode(coll);
                    _buzz.PlayNoise(150);
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

void AsteroidsGame::Loop()
{
    unsigned long time = millis();
    float elapsed = (float)(time - _lastLoop) / 1000.0;
    _lastshot += elapsed;

    if(gamestage == 0)
    {
        _tft->drawString("ASTEROIDS", _tft->width() / 2 - 30, _tft->height() / 2 - 10, 1);
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
   
        int asteroidsleft = std::count_if(_objects.begin(), _objects.end(), [](GameObject *go) { return go->ObjectType == 2; });

        if(asteroidsleft == 0)
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
        _tft->drawString("GAME OVER", _tft->width() / 2 - 30, _tft->height() / 2 - 10, 1);
        if(_rotary->Switch1Pressed || _rotary->Switch2Pressed)
        {
            _tft->fillScreen(BLACK);
            delay(500);
            gamestage = 0;
        }
    }

    _lastLoop = time;
    _firstloop = false;
}



GameObject* AsteroidsGame::CollisionCheck(GameObject *go, int objecttype)
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

void AsteroidsGame::Explode(GameObject *go)
{
    int num = go->PolygonPoints / 2;
    if(num < 1)
        num = 1;

    for(int i = 0; i < num; i++)
    {
        Debris *debr = new Debris();
        debr->Setup(go);
        _objects.push_back(debr);
    }

    go->RemoveFromScreen(_tft);
}