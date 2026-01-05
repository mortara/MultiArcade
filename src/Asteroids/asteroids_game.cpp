#include "asteroids_game.hpp"
#include "../general/config.h"

AsteroidsGame::AsteroidsGame(TFT_eSPI* screen, RotaryEncoder *player1paddle) : Game(screen)
{
    _tft = screen;
    
    _rotary = player1paddle;
    _world = new GameWorld(screen);
    _ship = new Ship(_rotary);

    Serial.print("Asteroids initialized!");
}

void AsteroidsGame::StartLevel(int l)
{
    level = l;
   
    _tft->fillScreen(DEFAULT_BG_COLOR);

    _ship->Position = Vector2DF(ScreenWidth/2,ScreenHeight/2);
    _ship->Velocity = Vector2DF(0,0);
    _ship->Render(_tft, true);
    
    _world->Clear();

    int numa = 3 + l;
    for(int i = 0; i < numa; i++)
    {    
        int sc = 3; // We want Size 3 asteroids

        if(random(50) < (l*3))
            sc = 4;         // but sometimes size 4 ones. the higher the level, the more size 4 asteroids are coming

        Asteroid *ast = new Asteroid(sc, ScreenWidth, ScreenHeight);
        ast->Render(_tft, true);
        _world->AddObject(ast);
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
    GameObject *shipcoll = _world->CollisionCheck(_ship, 2);
    if(shipcoll != NULL)
    {
        
        _world->Explode(shipcoll);
        _world->Explode(_ship);

        _buzz->PlayNoise(350);
        
        shipcoll->Delete = true;

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
    }

    if(fire && _lastshot >= _reloadtime)
    {
        Bullet *bullet = new Bullet(_ship);
        _world->AddObject(bullet);
        _lastshot = 0;

        _buzz->PlayTone(100, 50);
    }
}

void AsteroidsGame::ProcessObjects(float elapsed)
{
    std::list<GameObject *>* _objects = _world->GetObjects();
    for (GameObject *obj : *_objects)
    {
        if(obj->ObjectType == 3 && !obj->Delete)
        {
            GameObject *coll = _world->CollisionCheck(obj, 2);
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
                        Asteroid *asn = new Asteroid(s-1, ScreenWidth, ScreenHeight);
                        asn->Position = ast->Position;
                        asn->Velocity = ast->Velocity * (double)1.5;
                        _world->AddObject(asn);
                    }
                    _buzz->PlayNoise(300);
                }
                else
                {
                    _world->Explode(coll);
                    _buzz->PlayNoise(300);
                }
            }
        }
    }
}

void AsteroidsGame::Loop()
{
    unsigned long time = millis();
    float elapsed = (float)(time - _lastLoop) / 1000.0;
    _lastshot += elapsed;

    // Move all the Objects
    _world->Loop(elapsed);

    if(GameStage == 0)
    {
        _tft->drawString("ASTEROIDS", ScreenWidth / 2 - 30, ScreenHeight / 2 - 10, 1);
        if(_rotary->Switch1Pressed || _rotary->Switch2Pressed)
        {
            _tft->fillScreen(DEFAULT_BG_COLOR);
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
   
        int asteroidsleft = _world->CountObjects(2);

        if(asteroidsleft == 0)
        {
            score += level * 5;
            StartLevel(level + 1);
        }

        scores();
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
    }

    _lastLoop = time;
}