
#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>

#include "../general/config.h"
#include "pong.hpp"

void Pong::midline() {

  // If the ball is not on the line then don't redraw the line
  if ((( (int16_t)ball_x < (dashline_x-ball_w) ) || ( (int16_t)ball_x > (dashline_x+dashline_w))) && !firstloop) 
    return;

  tft.startWrite();

  // Quick way to draw a dashed line
  tft.setAddrWindow(dashline_x, 0, dashline_w, h);
  
  for(int16_t i = 0; i < dashline_n; i+=2) {
    tft.pushColor(WHITE, dashline_w*dashline_h); // push dash pixels
    tft.pushColor(BLACK, dashline_w*dashline_h); // push gap pixels
  }

  tft.endWrite();
}

void Pong::paddle(bool player, bool leftside, float &d, int16_t x, float &y, float &y_old) {
  
  bool redraw = true;
  if (y != y_old )
  {
    tft.fillRect(x, (int)y_old, paddle_w, (int)paddle_h, BLACK);
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

  if ((int)y + paddle_h >= h && d > 0) 
    d = 0;
  else if ((int)y <= 0 && d < 0) 
    d = 0;

  if(redraw || firstloop)
    tft.fillRect((int)x, (int)y, paddle_w, paddle_h, WHITE);
}

void Pong::calc_target_y() {
  int16_t target_x;
  int16_t reflections;
  int16_t y;

  if (ball_dx == 1) {
    target_x = w - ball_w;
  } 
  else {
    target_x = -1 * (w - ball_w);
  }

  y = abs(target_x * (ball_dy / ball_dx) + ball_y);

  reflections = floor(y / h);

  if (reflections % 2 == 0) {
    target_y = y % h;
  } 
  else {
    target_y = h - (y % h);
  }
}

void Pong::ball(float elapsed) {
    ball_x = ball_x + ball_dx * elapsed * ball_vmul;
    ball_y = ball_y + ball_dy * elapsed * ball_vmul;

    if (ball_dx < 0.0 && (int)ball_x == paddle_w && (int)ball_y + ball_h >= lpaddle_y && (int)ball_y <= lpaddle_y + paddle_h) {
      ball_dx = ball_dx * -1.0;
      calc_target_y(); 
    } else if (ball_dx > 0.0 && (int)ball_x + ball_w == w - paddle_w && (int)ball_y + ball_h >= rpaddle_y && (int)ball_y <= rpaddle_y + paddle_h) {
      ball_dx = ball_dx * -1.0; 
      calc_target_y();
    } 

    if ((int)ball_y > h - ball_w || (int)ball_y < 0) {
      ball_dy = ball_dy * -1.0;
      ball_y += ball_dy; // Keep in bounds
    }

    if ((int)ball_x > w)
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
      tft.fillRect((int)oldball_x, (int)oldball_y, ball_w, ball_h, BLACK); // Less TFT refresh aliasing than line above for large balls
      tft.fillRect(   (int)ball_x,    (int)ball_y, ball_w, ball_h, WHITE);
      oldball_x = ball_x;
      oldball_y = ball_y;
    }
}

void Pong::scores()
{
    if(singleplayer)
    {
        tft.drawString("Level: " + String(rscore) , 90, 2 , 2);
    }
    else
    {
        tft.drawString("P1: " + String(lscore) , 10, 2 , 2);
        tft.drawString("P2: " + String(rscore) , 120, 2 , 2);

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

void Pong::Setup(TFT_eSPI screen, RotaryEncoder *player1) {
  tft = screen;
  _player1paddle = player1;

  lpaddle_y = random(0, h - paddle_h);
  rpaddle_y = random(0, h - paddle_h);

  player1->Counter = 0;
  _player1LastpaddleCount = 0;

  // ball is placed on the center of the left paddle
  ball_y = lpaddle_y + (paddle_h / 2);
  
  calc_target_y();

  tft.fillScreen(BLACK);
  _lastLoop = millis();

  singleplayer = true;
  rscore = 1;
  lscore = 3;
}

void Pong::Setup(TFT_eSPI screen, RotaryEncoder *player1, RotaryEncoder *player2) {
  tft = screen;
  _player1paddle = player1;
  _player2paddle = player2;

  lpaddle_y = random(0, h - paddle_h);
  rpaddle_y = random(0, h - paddle_h);

  player1->Counter = 0;
  _player1LastpaddleCount = 0;

  player2->Counter = 0;
  _player2LastpaddleCount = 0;

  // ball is placed on the center of the left paddle
  ball_y = lpaddle_y + (paddle_h / 2);
  
  tft.fillScreen(BLACK);
  _lastLoop = millis();

  singleplayer = false;
  rscore = 0;
  lscore = 0;
}
