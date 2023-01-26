#include "breakout_game.hpp"

void BreakoutGame::Setup(TFT_eSPI screen, RotaryEncoder *player1paddle)
{
    _tft = screen;
    _tft.fillScreen(BLACK);

    _rotary = player1paddle;
    _lastrotarycount = _rotary->Counter;

    _paddle = new GameObject();
    _paddle->Position.X = _tft.width() / 2;
    _paddle->Position.Y = _tft.height() - 20;
    _paddle->Size = Vector2DF(18,2);

    _ball = new GameObject();
    _ball->Size = Vector2DF(2,2);

    _buzz = Buzzer();
    _buzz.Setup();
    
    Serial.print("Breakout initialized!");

    delay(500);

    _lastLoop = millis();
}

void BreakoutGame::StartLevel(int l)
{
    level = l;

    int rows = 3 + l;
    int bpr = 9;
    int bh = 5;
    int bw = (_tft.width() - 4) / (bpr + 1);

    if(rows > 7)
        rows = 7;

    for(int r = 0; r <= rows; r++)
    {
        uint16_t rc = WHITE;
        switch(r)
        {
            case 0:
                rc = TFT_BLUE;
                break;
            case 1: 
                rc = TFT_GREEN;
                break;
            case 2:
                rc = TFT_YELLOW;
                break;
            case 3:
                rc = TFT_GREEN;
                break;
            case 4:
                rc = TFT_RED;
                break;
            case 5:
                rc = TFT_BROWN;
                break;
            case 6:
                rc = TFT_CYAN;
                break;
        }


        for(int c = 0; c <= bpr; c++)
        {
            Block* block = new Block();

            block->Size = Vector2DF(bw, bh);
            block->Position = Vector2DF(2 + c * (bw+1),  15 + r * (bh+1));

            block->Setup(rc);

            _objects.push_back(block);
            block->Render(_tft);
        }
    }

    float startspeed = ballbasespeed + l * ballspeedlvlmultiplier;
    float startangle = 30.0f + random(30);
    if(random(100) > 50)
        startangle = 360 - startangle;

    float angle = (startangle - 90.0f) / 360.0f * 2.0f * PI;

    _ball->Position.X = _paddle->Position.X + _paddle->Size.X / 2.0f;
    _ball->Position.Y = _paddle->Position.Y - _ball->Size.Y - 4;
    _ball->Velocity.X = cos(angle) * startspeed;
    _ball->Velocity.Y = sin(angle) * startspeed;

}

void BreakoutGame::scores()
{
    _tft.drawString("Lives: " + String(lives) + " Score: " + String(score) , 10, 1 , 1); 
}

void BreakoutGame::ball(float elapsed) 
{
    bool redraw = false;
    if (_ball->Position.X != _ball->OldPosition.X || _ball->Position.Y != _ball->OldPosition.Y)
    {
        _tft.fillRect((int)_ball->OldPosition.X, (int)_ball->OldPosition.Y, (int)_ball->Size.X, (int)_ball->Size.Y, BLACK);
        redraw = true;
    } 
    
    //_tft.drawString("VX:" + String(_ball->vX) + ", VY:" + "VY:" + String(_ball->vY), 10, 15, 1);

    _ball->OldPosition = _ball->Position;

    _ball->Position.X +=  _ball->Velocity.X * elapsed;
    _ball->Position.Y +=  _ball->Velocity.Y * elapsed;

    if((_ball->Position.X <= 0 && _ball->Velocity.X < 0) || ((_ball->Position.X + _ball->Size.X) >= _tft.width() && _ball->Velocity.X > 0))
        _ball->Velocity.X *= -1.0f;
    else if(_ball->Position.Y <= 0 && _ball->Velocity.Y < 0)
        _ball->Velocity.Y *= -1.0f;
    else if((_ball->Position.Y + _ball->Size.Y) > _tft.height() && _ball->Velocity.Y > 0)
    {
        lives--;

        if(lives == 0)
        {
            _tft.fillScreen(BLACK);
            gamestage = 2;
            return;
        }

        _ball->Position.X = _paddle->Position.X + _paddle->Size.X / 2.0f;
        _ball->Position.Y = _paddle->Position.Y - _ball->Size.Y - 4;
        _ball->Velocity.Y *= -1.0f;
    //    _ball->vY *= -1.0f;
    }
    else if(_ball->Velocity.Y > 0 && ((_ball->Position.Y + _ball->Size.Y) >= _paddle->Position.Y && _ball->Position.Y < _paddle->Position.Y + _paddle->Size.Y) && ((_ball->Position.X + _ball->Size.X) >= _paddle->Position.X && _ball->Position.X <= (_paddle->Position.X + _paddle->Size.X)))
    {
        _ball->Velocity.Y *= -1.0f;
        
        float d = - (_ball->Position.X - _paddle->Position.X - _paddle->Size.X / 2.0f) / (_paddle->Size.X / 2.0f);
        if((d > 0.9 && _ball->Velocity.X > 0) || (d < -0.9 && _ball->Velocity.X < 0))
            _ball->Velocity.X *= -1.0f;
        else if((d > 0.7 && _ball->Velocity.X > 0) || (d < -0.7 && _ball->Velocity.X < 0))
            _ball->Velocity.X *= -0.8f;

        _buzz.PlayTone(200, 50);
        _tft.drawString("d:" + String(d), 10, 15, 1);
    }
    else
    {
        std::list<Block *> _removedobjects;

        for (Block *obj : _objects)
        {
            if(obj->CollidesWith(_ball))
            {
                score += 5;
                _removedobjects.push_back(obj);
                obj->RemoveFromScreen(_tft);

                if((_ball->Position.X + _ball->Size.X) > obj->Position.X && _ball->Position.X  < obj->Position.X + obj->Size.X)
                    _ball->Velocity.Y *= -1.0f;
                else if((_ball->Position.Y + _ball->Size.Y) > obj->Position.Y && _ball->Position.Y  < (obj->Position.Y + obj->Size.Y))
                    _ball->Velocity.X *= -1.0f;
                else
                {
                    _ball->Velocity.Y *= -1.0f;
                    _ball->Velocity.X *= -1.0f;
                }


                _buzz.PlayTone(400, 50);

                break;
            }
        }

        for (Block *obj : _removedobjects)
            _objects.remove(obj);

        if(_objects.empty())
        {
            StartLevel(level + 1);
        }
    }

    if(redraw || firstloop)
        _tft.fillRect((int)_ball->Position.X, (int)_ball->Position.Y, (int)_ball->Size.X, (int)_ball->Size.Y, WHITE);
}

void BreakoutGame::paddle() {
  
  bool redraw = false;
  if (_paddle->Position.X != _paddle->OldPosition.X )
  {
    _tft.fillRect((int)_paddle->OldPosition.X, (int)_paddle->Position.Y, (int)_paddle->Size.X, (int)_paddle->Size.Y, BLACK);
    redraw = true;
  } 
  
  _paddle->OldPosition = _paddle->Position;
  _paddle->Position =  _paddle->Position + _paddle->Velocity ;
  
  int paddle1count =  _rotary->Counter;  
  _paddle->Velocity.X = (paddle1count - _lastrotarycount) * paddle_v ;
  _lastrotarycount = paddle1count;

  if ((int)_paddle->Position.X + _paddle->Size.X >= _tft.width() && _paddle->Velocity.X > 0) 
    _paddle->Velocity.X = 0;
  else if ((int)_paddle->Position.X <= 0 && _paddle->Velocity.X < 0) 
    _paddle->Velocity.X = 0;

  if(redraw || firstloop)
    _tft.fillRect((int)_paddle->Position.X, (int)_paddle->Position.Y, (int)_paddle->Size.X, (int)_paddle->Size.Y, WHITE);
}

void BreakoutGame::Loop()
{
    long time = millis();
    double elapsed = (double)(time - _lastLoop) / 1000.0;
  
    if(gamestage == 0)
    {
        _tft.drawString("BREAKOUT", _tft.width() / 2 - 30, _tft.height() / 2 - 10, 1);
        if(_rotary->Switch1Pressed || _rotary->Switch2Pressed)
        {
            _tft.fillScreen(BLACK);
            score = 0;
            lives = 3;
            gamestage = 1;
            StartLevel(1);
            delay(500);
        }
    }
    if(gamestage == 1)
    {
        scores();
        paddle();
        ball(elapsed);       
    }

    if(gamestage == 2)
    {
        _tft.drawString("GAME OVER", _tft.width() / 2 - 30, _tft.height() / 2 - 10, 1);
        if(_rotary->Switch1Pressed || _rotary->Switch2Pressed)
        {
            _tft.fillScreen(BLACK);
            delay(500);
            gamestage = 0;
        }
    }

    _lastLoop = time;

    //_tft.drawString("ball: " + String(_ball->Position.X) + ", " + String(_ball->Position.Y) + " ", 10, 10 , 2);
}