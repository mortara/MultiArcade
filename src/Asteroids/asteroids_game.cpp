#include "asteroids_game.h"
#include "../general/config.h"

void AsteroidsGame::Setup(TFT_eSPI screen, RotaryEncoder *player1paddle, int16_t screen_width, int16_t screen_height)
{
    w = screen_width;
    h = screen_height;

    _tft = screen;
    _tft.fillScreen(BLACK);

    _rotary = player1paddle;

    _ship = new Ship();
    _ship->Setup(_rotary);
    

    
    Serial.print("Asteroids initialized!");
}

void AsteroidsGame::StartLevel(int l)
{
    level = l;

    _ship->Position.X = w / 2;
    _ship->Position.Y = h / 2;
    _ship->Velocity.X = 0;
    _ship->Velocity.Y = 0;
    _ship->Rotation = 0;

    int numa = 3 + l;
    _objects.clear();
    for(int i = 0; i < numa; i++)
    {
        Asteroid *ast = new Asteroid();
        int sc = 3; // We want Size 3 asteroids

        if(random(50) < (l*3))
            sc = 4;         // but sometimes size 4 ones. the higher the level, the more size 4 asteroids are coming

        ast->Setup(sc, w, h);
        _objects.push_back(ast);
    }

}

void AsteroidsGame::scores()
{
    _tft.drawString("Lvl: " + String(level) + " Score: " + String(score) + " Ships: " + String(lives) , 5, 1 , 1);
    
}

void AsteroidsGame::Loop()
{
    unsigned long time = millis();
    double elapsed = (double)(time - _lastLoop) / 1000.0;
    _lastshot += elapsed;

    if(gamestage == 0)
    {
        _tft.drawString("ASTEROIDS", w / 2 - 30, h / 2 - 10, 1);
        if(_rotary->Switch1Pressed || _rotary->Switch2Pressed)
        {
            _tft.fillScreen(BLACK);
            score = 0;
            gamestage = 1;
            lives = 3;
            StartLevel(1);
            delay(500);
        }
    }

    if(gamestage == 1)
    {
        bool fire = _ship->Control();
        _ship->Move(elapsed);
        _ship->Render(_tft);

        OutOfBoundsCheck(_ship);
        GameObject *shipcoll = CollisionCheck(_ship, 2);
        if(shipcoll != NULL)
        {
            _tft.fillScreen(BLACK);
            delay(1500);
            lives--;
            if(lives == 0)
            {
                gamestage = 2;
                return;
            }
            else
                StartLevel(level);
        }

        std::list<GameObject *> _removedobjects;

        for (GameObject *obj : _objects)
        {
            obj->Move(elapsed);
            obj->Render(_tft);      
            if(OutOfBoundsCheck(obj))
                _removedobjects.push_back(obj);

            if(obj->ObjectType == 3)
            {
                GameObject *coll = CollisionCheck(obj, 2);
                if(coll != NULL)
                {
                    score+=((Asteroid*)coll)->Sizeclass * 5;
                    _removedobjects.push_back(coll);
                    _removedobjects.push_back(obj);

                    Asteroid *ast = (Asteroid *)coll;
                    int s = ast->Sizeclass;

                    if(s > 2)
                    {
                        for(int i = 0; i < s; i++)
                        {
                            Asteroid *asn = new Asteroid();
                            asn->Setup(s-1, w, h);
                            asn->Position.X = ast->Position.X;
                            asn->Position.Y = ast->Position.Y;
                            asn->Velocity = asn->Velocity * (double)1.5;
                            _objects.push_back(asn);
                        }
                    }
                }
            }
        }

        if(fire && _lastshot >= _reloadtime)
        {
            Bullet *bullet = new Bullet();
            bullet->Setup(_ship);
            _objects.push_back(bullet);
            _lastshot = 0;
        }

        for (GameObject *obj : _removedobjects)
        {
            obj->RemoveFromScreen(_tft);
            _objects.remove(obj);
        }

        _removedobjects.clear();

        int asteroidsleft = 0;
        for (GameObject *obj : _objects)
        {
            if(obj->ObjectType == 2)
            asteroidsleft++;
        }

        if(asteroidsleft == 0)
        {
            score += level * 5;
            StartLevel(level + 1);
        }

        scores();
    }

    if(gamestage == 2)
    {
        _tft.drawString("GAME OVER", w / 2 - 30, h / 2 - 10, 1);
        if(_rotary->Switch1Pressed || _rotary->Switch2Pressed)
        {
            _tft.fillScreen(BLACK);
            delay(500);
            gamestage = 0;
        }
    }

    _lastLoop = time;

    //_tft.drawString("ShipPos: " + String(_ship->X) + ", " + String(_ship->Y) + " ", 10, 10 , 2);
}

bool AsteroidsGame::OutOfBoundsCheck(GameObject *go)
{
    // Nothing happens when object leaves the screen
    if(go->OutOfBoundsMethod == 0)
        return false;

    // When leaving the screen on one side, the object will return to screen on the other
    if(go->OutOfBoundsMethod == 1)
    {
        int16_t margin = 8;

        if((go->Position.X - go->Size.X - margin) > w && go->Velocity.X >= 0)
            go->Position.X = 0 - margin;

        if((go->Position.Y - go->Size.Y - margin) > h && go->Velocity.Y >= 0)
            go->Position.Y = 0 - margin;
        
        if((go->Position.X + go->Size.X + margin) < 0 && go->Velocity.X <= 0)
            go->Position.X = w + margin;

        if((go->Position.Y + go->Size.Y + margin) < 0 && go->Velocity.Y <= 0)
            go->Position.Y = h + margin;

        return false;
    }

    // When leaving the screen, object will be deleted
    if(go->OutOfBoundsMethod == 2)
    {
        int16_t margin = 16;
 
        if((go->Position.X - go->Size.X - margin) > w || (go->Position.Y - go->Size.Y - margin) > h || (go->Position.X + go->Size.X + margin) < 0 || (go->Position.Y + go->Size.Y + margin) < 0)
        {
            return true;
        }

    }

    return false;
}

GameObject* AsteroidsGame::CollisionCheck(GameObject *go, int objecttype)
{
    for (GameObject *obj : _objects)
    {
        if(obj->ObjectType != objecttype)
            continue;

        if(go->Intersects(obj))
            return obj;

    }

    return NULL;
}