#include "breakout_game.hpp"

void BreakoutGame::Setup(TFT_eSPI screen, RotaryEncoder *player1paddle, int16_t screen_width, int16_t screen_height)
{
    w = screen_width;
    h = screen_height;

    _tft = screen;
    _tft.fillScreen(BLACK);

    _rotary = player1paddle;
    _lastrotarycount = _rotary->Counter;

    _paddle = new GameObject();
    _paddle->Position.X = screen_width / 2;
    _paddle->Position.Y = screen_height - 20;
    _paddle->w = 15;
    _paddle->h = 2;

    _ball = new GameObject();
    _ball->w = 2;
    _ball->h = 2;
    _ball->Position.X = _paddle->Position.X + _paddle->w / 2.0f;
    _ball->Position.Y = _paddle->Position.Y - _ball->h - 4;

    float startspeed = 55;
    float startangle = 300.0f + random(120);

    float angle = (startangle - 90.0f) / 360.0f * 2.0f * PI;

    _ball->vX = cos(angle) * startspeed;
    _ball->vY = sin(angle) * startspeed;
    
    Serial.print("Breakout initialized!");

    _lastLoop = millis();
}

void BreakoutGame::scores()
{
    //_tft.drawString("Level: " + String(level) + "   Score: " + String(score) , 10, 2 , 2); 
}

void BreakoutGame::ball(float elapsed) 
{
    bool redraw = false;
    if (_ball->Position.X != _ball->OldPosition.X || _ball->Position.Y != _ball->OldPosition.Y)
    {
        _tft.fillRect((int)_ball->OldPosition.X, (int)_ball->OldPosition.Y, (int)_ball->w, (int)_ball->h, BLACK);
        redraw = true;
    } 
    
    _ball->OldPosition.X = _ball->Position.X;
    _ball->Position.X +=  _ball->vX * elapsed;

    _ball->OldPosition.Y = _ball->Position.Y;
    _ball->Position.Y +=  _ball->vY * elapsed;

    if((_ball->Position.X <= 0 && _ball->vX < 0) || ((_ball->Position.X + _ball->w) >= w && _ball->vX > 0))
        _ball->vX *= -1.0f;

    if(_ball->Position.Y <= 0 && _ball->vY < 0)
        _ball->vY *= -1.0f;

    if(_ball->Position.Y > h && _ball->vY > 0)
    {
        lives--;

        if(lives == 0)
        {
            gamestage = 2;
            return;
        }

        _ball->Position.X = _paddle->Position.X + _paddle->w / 2.0f;
        _ball->Position.Y = _paddle->Position.Y - _ball->h - 4;
        _ball->vY *= -1.0f;
    //    _ball->vY *= -1.0f;
    }

    if(_ball->vY > 0 && _ball->Position.Y >= _paddle->Position.Y && (_ball->Position.X >= _paddle->Position.X && _ball->Position.X <= (_paddle->Position.X + _paddle->w)))
    {
        _ball->vY *= -1.0f;
        _ball->vX += _paddle->vX * elapsed * 0.5;
    }

    if(redraw || firstloop)
        _tft.fillRect((int)_ball->Position.X, (int)_ball->Position.Y, (int)_ball->w, (int)_ball->h, WHITE);
}

void BreakoutGame::paddle() {
  
  bool redraw = false;
  if (_paddle->Position.X != _paddle->OldPosition.X )
  {
    _tft.fillRect((int)_paddle->OldPosition.X, (int)_paddle->Position.Y, (int)_paddle->w, (int)_paddle->h, BLACK);
    redraw = true;
  } 
  
  _paddle->OldPosition.X = _paddle->Position.X;
  _paddle->Position.X +=  _paddle->vX ;
  
  int paddle1count =  _rotary->Counter;  
  _paddle->vX = (paddle1count - _lastrotarycount) * paddle_v ;
  _lastrotarycount = paddle1count;

  if ((int)_paddle->Position.X + _paddle->w >= w && _paddle->vX > 0) 
    _paddle->vX = 0;
  else if ((int)_paddle->Position.X <= 0 && _paddle->vX < 0) 
    _paddle->vX = 0;

  if(redraw || firstloop)
    _tft.fillRect((int)_paddle->Position.X, (int)_paddle->Position.Y, (int)_paddle->w, (int)_paddle->h, WHITE);
}

void BreakoutGame::Loop()
{
    long time = millis();
    double elapsed = (double)(time - _lastLoop) / 1000.0;
  
    if(gamestage == 0)
    {
        _tft.drawString("BREAKOUT", w / 2 - 40, h / 2, 1);
        if(_rotary->SW2 == 0 || _rotary->SW == 0)
        {
            score = 0;
            lives = 3;
            gamestage = 1;
        }
    }
    if(gamestage == 1)
    {
        paddle();
        ball(elapsed);
        scores();
    }

    if(gamestage == 2)
    {
        _tft.drawString("GAME OVER", w / 2 - 50, h / 2, 1);
        if(_rotary->SW2 == 0 || _rotary->SW == 0)
            gamestage = 0;
    }

    _lastLoop = time;

    //_tft.drawString("ball: " + String(_ball->Position.X) + ", " + String(_ball->Position.Y) + " ", 10, 10 , 2);
}