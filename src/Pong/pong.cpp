
#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>

#include "../general/config.h"
#include "pong.h"

void Pong::midline() {

  // If the ball is not on the line then don't redraw the line
  if (((int)ball_x<dashline_x-ball_w) && ((int)ball_x > dashline_x+dashline_w)) return;

  tft.startWrite();

  // Quick way to draw a dashed line
  tft.setAddrWindow(dashline_x, 0, dashline_w, h);
  
  for(int16_t i = 0; i < dashline_n; i+=2) {
    tft.pushColor(WHITE, dashline_w*dashline_h); // push dash pixels
    tft.pushColor(BLACK, dashline_w*dashline_h); // push gap pixels
  }

  tft.endWrite();
}

void Pong::lpaddle() {
  
  if (lpaddle_d == 1) {
    tft.fillRect(lpaddle_x, lpaddle_y, paddle_w, 1, BLACK);
  } 
  else if (lpaddle_d == -1) {
    tft.fillRect(lpaddle_x, lpaddle_y + paddle_h - 1, paddle_w, 1, BLACK);
  }

  lpaddle_y = lpaddle_y + lpaddle_d;

  if (ball_dx == 1) lpaddle_d = 0;
  else {
    if (lpaddle_y + paddle_h / 2 == target_y) lpaddle_d = 0;
    else if (lpaddle_y + paddle_h / 2 > target_y) lpaddle_d = -1;
    else lpaddle_d = 1;
  }

  if (lpaddle_y + paddle_h >= h && lpaddle_d == 1) lpaddle_d = 0;
  else if (lpaddle_y <= 0 && lpaddle_d == -1) lpaddle_d = 0;

  tft.fillRect(lpaddle_x, lpaddle_y, paddle_w, paddle_h, WHITE);
}

void Pong::rpaddle(bool player) {
  
  if (rpaddle_d > 0) {
    tft.fillRect(rpaddle_x, (int)rpaddle_y, paddle_w, (int)rpaddle_d, BLACK);
  } 
  else if (rpaddle_d < 0) {
    tft.fillRect(rpaddle_x, (int)rpaddle_y + paddle_h + (int)rpaddle_d, paddle_w, (int)-rpaddle_d, BLACK);
  }

  rpaddle_y = rpaddle_y + rpaddle_d ;
  
  if(!player)
  {
    if (ball_dx == -1) rpaddle_d = 0;
    else {
      if ((int)rpaddle_y + paddle_h / 2 == target_y) rpaddle_d = 0;
      else if ((int)rpaddle_y + paddle_h / 2 > target_y) rpaddle_d = -1;
      else rpaddle_d = 1;
    }
  }
  else
  {
    int paddle1count =  _player1paddle->Counter;
   
    rpaddle_d = (paddle1count - _player1LastpaddleCount) * rpaddle_v ;

    _player1LastpaddleCount = paddle1count;
  }

  if ((int)rpaddle_y + paddle_h >= h && rpaddle_d == 1) rpaddle_d = 0;
    else if ((int)rpaddle_y <= 0 && rpaddle_d == -1) rpaddle_d = 0;

  tft.fillRect(rpaddle_x, (int)rpaddle_y, paddle_w, paddle_h, WHITE);
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
    }

    //tft.fillRect(oldball_x, oldball_y, ball_w, ball_h, BLACK);
    tft.drawRect((int)oldball_x, (int)oldball_y, ball_w, ball_h, BLACK); // Less TFT refresh aliasing than line above for large balls
    tft.fillRect(   (int)ball_x,    (int)ball_y, ball_w, ball_h, WHITE);
    oldball_x = ball_x;
    oldball_y = ball_y;
}

void Pong::Loop() {

    long time = millis();
    double elapsed = (double)(time - _lastLoop) / 1000.0;

    lpaddle();
    rpaddle(true);

    midline();

    ball(elapsed);

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

  midline();
  tft.fillScreen(BLACK);
  _lastLoop = millis();

}
