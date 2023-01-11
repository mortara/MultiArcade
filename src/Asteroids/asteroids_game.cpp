#include "asteroids_game.h"
#include "../general/config.h"

void AsteroidsGame::Setup(TFT_eSPI screen, RotaryEncoder *player1paddle, int16_t screen_height, int16_t screen_width)
{
    h = screen_width;
    w = screen_height;

    _tft = screen;
    _tft.fillScreen(BLACK);

    _rotary = player1paddle;

    _ship = new Ship();
    _ship->Setup(_rotary);
    _ship->Position.X = 80;
    _ship->Position.Y = 64;

    for(int i = 0; i < 6; i++)
    {
        Asteroid *ast = new Asteroid();
        ast->Setup(3);
        _objects.push_back(ast);
    }

    Serial.print("Asteroids initialized!");
}

void AsteroidsGame::Loop()
{
    long time = millis();
    double elapsed = (double)(time - _lastLoop) / 1000.0;
    _lastshot += elapsed;

    bool fire = _ship->Control();
    _ship->Move(elapsed);
    _ship->Render(_tft);

    OutOfBoundsCheck(_ship);

    for (GameObject *obj : _objects)
    {
        obj->Move(elapsed);
        obj->Render(_tft);      
        OutOfBoundsCheck(obj);

        if(obj->ObjectType == 3)
        {
            GameObject *coll = CollisionCheck(obj);
            if(coll != NULL && coll->ObjectType == 2)
            {
                Asteroid *ast = (Asteroid *)coll;
                int s = ast->Sizeclass;

                if(s > 1)
                {
                    for(int i = 0; i < s; i++)
                    {
                        Asteroid *asn = new Asteroid();
                        asn->Setup(s-1);
                        asn->Position.X = ast->Position.X;
                        asn->Position.Y = ast->Position.Y;
                        asn->vX *= 1.5f;
                        asn->vY *= 1.5f;
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

    _lastLoop = time;

    //_tft.drawString("ShipPos: " + String(_ship->X) + ", " + String(_ship->Y) + " ", 10, 10 , 2);
}

void AsteroidsGame::OutOfBoundsCheck(GameObject *go)
{
    // Nothing happens when object leaves the screen
    if(go->OutOfBoundsMethod == 0)
        return;

    // When leaving the screen on one side, the object will return to screen on the other
    if(go->OutOfBoundsMethod == 1)
    {
        int16_t margin = 8;

        if((go->Position.X - go->w - margin) > w && go->vX > 0)
            go->Position.X = 0 - 2 * margin;

        if((go->Position.Y - go->h - margin) > h && go->vY > 0)
            go->Position.Y = 0 - 2 * margin;
        
        if((go->Position.X + go->w + margin) < 0 && go->vX < 0)
            go->Position.X = w + 2 * margin;

        if((go->Position.Y + go->h + margin) < 0 && go->vY < 0)
            go->Position.Y = h + 2 * margin;
    }

    // When leaving the screen, object will be deleted
    if(go->OutOfBoundsMethod == 2)
    {
        int16_t margin = 8;
 
        if((go->Position.X - go->w - margin) > w || (go->Position.Y - go->h - margin) > h || (go->Position.X + go->w + margin) < 0 || (go->Position.Y + go->h + margin) < 0)
            _removedobjects.push_back(go);

    }
}

GameObject* AsteroidsGame::CollisionCheck(GameObject *go)
{
    for (GameObject *obj : _objects)
    {
        if(obj->ObjectType != 2)
            continue;

        float distance = go->Position.Distance(obj->Position);
        if(distance < 8)
        {
            _removedobjects.push_back(go);
            _removedobjects.push_back(obj);
            return obj;
        }
    }

    return NULL;
}