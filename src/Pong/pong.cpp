#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>

#define BLACK 0x0000
#define WHITE 0xFFFF
#define GREY  0x5AEB

TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h

int16_t h = 124;
int16_t w = 156;

int dly = 10;

int16_t paddle_h = 25;
int16_t paddle_w = 2;

int16_t lpaddle_x = 0;
int16_t rpaddle_x = w - paddle_w;

int16_t lpaddle_y = 0;
int16_t rpaddle_y = h - paddle_h;

int16_t lpaddle_d = 1;
int16_t rpaddle_d = -1;

int16_t lpaddle_ball_t = w - w / 4;
int16_t rpaddle_ball_t = w / 4;

int16_t target_y = 0;

int16_t ball_x = 2;
int16_t ball_y = 2;
int16_t oldball_x = 2;
int16_t oldball_y = 2;

int16_t ball_dx = 1;
int16_t ball_dy = 1;

int16_t ball_w = 4;
int16_t ball_h = 4;

int16_t dashline_h = 4;
int16_t dashline_w = 2;
int16_t dashline_n = h / dashline_h;
int16_t dashline_x = w / 2 - 1;
int16_t dashline_y = dashline_h / 2;

int16_t lscore = 12;
int16_t rscore = 4;



void loop() {
  // put your main code here, to run repeatedly:
  delay(dly);

  lpaddle();
  rpaddle();

  midline();

  ball();
}

void initgame() {
  lpaddle_y = random(0, h - paddle_h);
  rpaddle_y = random(0, h - paddle_h);

  // ball is placed on the center of the left paddle
  ball_y = lpaddle_y + (paddle_h / 2);
  
  calc_target_y();

  midline();

  tft.fillRect(0,h-26,w,h-1,BLACK);

  tft.setTextDatum(TC_DATUM);
  tft.setTextColor(WHITE);
  tft.drawString("TFT_eSPI example", w/2, h-26 , 2);
}

void setup() {
  // put your setup code here, to run once:

  randomSeed(analogRead(0)*analogRead(1));
   
  tft.init();

  tft.setRotation(1);

  tft.fillScreen(BLACK);
  
  initgame();

  tft.setTextColor(WHITE, BLACK);

  delay(2000);

}