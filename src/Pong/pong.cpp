#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>

#include "../general/config.h"
#include "pong.hpp"

void Pong::midline() {

    int16_t dashline_h = 4;
    int16_t dashline_w = 2;
    int16_t dashline_n = ScreenHeight / dashline_h;
    int16_t dashline_x = ScreenWidth / 2 - 1;
    int16_t dashline_y = dashline_h / 2;

    // If the ball is not on the line then don't redraw the line
    if ((( (int16_t)ball_x < (dashline_x-ball_w) ) || ( (int16_t)ball_x > (dashline_x+dashline_w))) && !firstloop) 
      return;

    _tft->startWrite();

    // Quick way to draw a dashed line
    _tft->setAddrWindow(dashline_x, 0, dashline_w, ScreenHeight);
    
    for(int16_t i = 0; i < dashline_n; i+=2) {
      _tft->pushColor(WHITE, dashline_w*dashline_h); // push dash pixels
      _tft->pushColor(DEFAULT_BG_COLOR, dashline_w*dashline_h); // push gap pixels
    }

    _tft->endWrite();
}

void Pong::paddle(bool player, bool leftside, float &d, int16_t x, float &y, float &y_old) {
  
  bool redraw = true;
  if (y != y_old )
  {
    _tft->fillRect(x, (int)y_old, paddle_w, (int)paddle_h, BLACK);
  } 
  else
  {
    redraw = false;
  }
  
  y_old = y;

  y = y + d ;
  
  if(!player)
  {
    if ((leftside && ball_dx > 0) || (!leftside && ball_dx < 0)) 
      d = 0;
    else {
      if ((int)y + paddle_h / 2 == target_y) 
        d = 0;
      else if ((int)y + paddle_h / 2 > target_y) 
        d = -0.2;
      else 
        d = 0.2;
    }
  }
  else
  {
    if(!leftside)
    {
      int paddle1count =  _player1paddle->Counter;  
      d = (paddle1count - _player1LastpaddleCount) * rpaddle_v ;
      _player1LastpaddleCount = paddle1count;
    }
    else
    {
      int paddle2count =  _player2paddle->Counter;  
      d = (paddle2count - _player2LastpaddleCount) * lpaddle_v ;
      _player2LastpaddleCount = paddle2count;
    }
  }

  if ((int)y + paddle_h >= ScreenHeight && d > 0) 
    d = 0;
  else if ((int)y <= 0 && d < 0) 
    d = 0;

  if(redraw || firstloop)
    _tft->fillRect((int)x, (int)y, paddle_w, paddle_h, WHITE);
}

void Pong::calc_target_y() {
  int16_t target_x;
  int16_t reflections;
  int16_t y;

  if (ball_dx == 1) {
    target_x = ScreenWidth - ball_w;
  } 
  else {
    target_x = -1 * (ScreenWidth - ball_w);
  }

  y = abs(target_x * (ball_dy / ball_dx) + ball_y);

  reflections = floor(y / ScreenHeight);

  if (reflections % 2 == 0) {
    target_y = y % ScreenHeight;
  } 
  else {
    target_y = ScreenHeight - (y % ScreenHeight);
  }
}

void Pong::ball(float elapsed) {
    ball_x = ball_x + ball_dx * elapsed * ball_vmul;
    ball_y = ball_y + ball_dy * elapsed * ball_vmul;

    if (ball_dx < 0.0 && (int)ball_x == paddle_w && (int)ball_y + ball_h >= lpaddle_y && (int)ball_y <= lpaddle_y + paddle_h) {
      ball_dx = ball_dx * -1.0;
      calc_target_y(); 
      _buzz->PlayTone(200, 50);
    } else if (ball_dx > 0.0 && (int)ball_x + ball_w == ScreenWidth - paddle_w && (int)ball_y + ball_h >= rpaddle_y && (int)ball_y <= rpaddle_y + paddle_h) {
      ball_dx = ball_dx * -1.0; 
      calc_target_y();
      _buzz->PlayTone(200, 50);
    } 

    if ((int)ball_y > ScreenHeight - ball_w || (int)ball_y < 0) {
      ball_dy = ball_dy * -1.0;
      ball_y += ball_dy; // Keep in bounds
    }

    if ((int)ball_x > ScreenWidth)
    {
        ball_x = 2;
        ball_y = lpaddle_y + (paddle_h / 2);

        if(singleplayer)
        {
          lscore -=1;
          if(lscore == 0)
          {
            // GameOver
          }
        }
        else
        {
          lscore++;
        }
    }

    if ((int)ball_x < 0 && !singleplayer)
    {
        ball_x = rpaddle_x - 4;
        ball_y = rpaddle_y + (paddle_h / 2);
        rscore++;
    }

    if(oldball_x != ball_x || oldball_y != ball_y || firstloop)
    {
      //tft.fillRect(oldball_x, oldball_y, ball_w, ball_h, BLACK);
      _tft->fillRect((int)oldball_x, (int)oldball_y, ball_w, ball_h, BLACK); // Less TFT refresh aliasing than line above for large balls
      _tft->fillRect(   (int)ball_x,    (int)ball_y, ball_w, ball_h, WHITE);
      oldball_x = ball_x;
      oldball_y = ball_y;
    }
}

void Pong::scores()
{
    if(singleplayer)
    {
        _tft->drawString("Level: " + String(rscore) , 90, 2 , 2);
    }
    else
    {
        _tft->drawString("P1: " + String(lscore) , 10, 2 , 2);
        _tft->drawString("P2: " + String(rscore) , 120, 2 , 2);

    }
}

void Pong::Loop() {

    long time = millis();
    float elapsed = (double)(time - _lastLoop) / 1000.0;

    if(singleplayer)
      paddle(false, true, lpaddle_d, lpaddle_x, lpaddle_y, lpaddle_y_old);
    else
      paddle(true, true, lpaddle_d, lpaddle_x, lpaddle_y, lpaddle_y_old);

    paddle(true, false, rpaddle_d, rpaddle_x, rpaddle_y, rpaddle_y_old);
    midline();
    ball(elapsed);
    scores();

    if(singleplayer)
    {
      currentleveltime += elapsed;
      if(currentleveltime >= maxleveltime)
      {
          currentleveltime -= maxleveltime;
          rscore++;
          ball_dx *= 1.1;
          ball_dy *= 1.1;
      }
    }

    firstloop = false;
    _lastLoop = time;
}

Pong::Pong(TFT_eSPI* screen, RotaryEncoder *player1) : Game(screen)
{
  rpaddle_x = ScreenWidth - paddle_w;
  rpaddle_y = ScreenHeight - paddle_h;
  rpaddle_y_old = rpaddle_y;
  _player1paddle = player1;
  _player2paddle = player1;
  
  lpaddle_y = random(0, ScreenHeight - paddle_h);
  rpaddle_y = random(0, ScreenHeight - paddle_h);

  player1->Counter = 0;
  _player1LastpaddleCount = 0;
  _player2LastpaddleCount = 0;

  // ball is placed on the center of the left paddle
  ball_y = lpaddle_y + (paddle_h / 2);
  
  calc_target_y();

  _tft->fillScreen(DEFAULT_BG_COLOR);
  _lastLoop = millis();

  singleplayer = true;
  rscore = 1;
  lscore = 3;
}

Pong::Pong(TFT_eSPI* screen, RotaryEncoder *player1, RotaryEncoder *player2) : Pong(screen, player1)
{
  _player2paddle = player2;
  player2->Counter = 0;
  _player2LastpaddleCount = 0;

  singleplayer = false;
  rscore = 0;
  lscore = 0;
}
