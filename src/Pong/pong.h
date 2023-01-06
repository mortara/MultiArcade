#include <Arduino.h>
#include <TFT_eSPI.h>

#include "../input/rotary_encoder.h"

class Pong
{
    private:
        long _lastLoop;

        TFT_eSPI tft;

        int16_t h = 124;
        int16_t w = 156;

        int dly = 10;

        int16_t paddle_h = 25;
        int16_t paddle_w = 2;

        int16_t lpaddle_x = 0;
        int16_t rpaddle_x = w - paddle_w;

        int16_t lpaddle_y = 0;
        float rpaddle_y = h - paddle_h;

        int16_t lpaddle_d = 1;
        float rpaddle_d = -1;
        float rpaddle_v = 2.0;

        int16_t lpaddle_ball_t = w - w / 4;
        int16_t rpaddle_ball_t = w / 4;

        int16_t target_y = 0;

        float ball_x = 2;
        float ball_y = 2;
        float oldball_x = 2;
        float oldball_y = 2;

        float ball_dx = 1;
        float ball_dy = 1;
        float ball_vmul = 50;

        int16_t ball_w = 4;
        int16_t ball_h = 4;

        int16_t dashline_h = 4;
        int16_t dashline_w = 2;
        int16_t dashline_n = h / dashline_h;
        int16_t dashline_x = w / 2 - 1;
        int16_t dashline_y = dashline_h / 2;

        int16_t lscore = 0;
        int16_t rscore = 0;

        long _player1LastpaddleCount;
        RotaryEncoder *_player1paddle;

        void midline();
        void lpaddle();
        void rpaddle(bool player);
        void calc_target_y();
        void ball(float elapsed);

    public:
        void Setup(TFT_eSPI screen, RotaryEncoder *player1);
        void Loop();
};