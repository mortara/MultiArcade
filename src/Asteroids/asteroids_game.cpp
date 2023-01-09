#include "asteroids_game.h"
#include "../general/config.h"

void AsteroidsGame::Setup(TFT_eSPI screen)
{
    _tft = screen;
    _tft.fillScreen(BLACK);

    _bullets = new Bullet[_numBullets];
    for(int i = 0; i < _numBullets; i++)
    {
        _bullets[i] = Bullet();
        _bullets[i].Enabled = 0;
    }

    _asteroids = new Asteroid[_numAsteroids];
    for(int i = 0; i < _numAsteroids; i++)
    {
        _asteroids[i] = Asteroid();
        _asteroids[i].Enabled = 0;
    }
}

void AsteroidsGame::Loop()
{
    long time = millis();
    double elapsed = (double)(time - _lastLoop) / 1000.0;

    _ship.Control();
    _ship.Move(elapsed);
    _ship.Render(_tft);

    for(int i = 0; i < _numAsteroids; i++)
    {
        if(_asteroids[i].Enabled)
        {
            _asteroids[i].Move(elapsed);
            _asteroids[i].Render(_tft);
        }
    }

    for(int i = 0; i < _numBullets; i++)
    {
        if(_bullets[i].Enabled)
        {
            _bullets[i].Move(elapsed);
            _bullets[i].Render(_tft);
        }
    }

    _lastLoop = time;
}