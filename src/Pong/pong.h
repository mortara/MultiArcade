#include <Arduino.h>
#include <TFT_eSPI.h>

#include "../input/rotary_encoder.h"

class Pong
{
    private:
        long _lastLoop;

        TFT_eSPI tft;

        int16_t h = 128;
        int16_t w = 160;

        int16_t paddle_h = 25;
        int16_t paddle_w = 2;

        int16_t lpaddle_x = 0;
        int16_t rpaddle_x = w - paddle_w;

        float lpaddle_y = 0;
        float rpaddle_y = h - paddle_h;
        float lpaddle_y_old = 0;
        float rpaddle_y_old = h - paddle_h;

        float lpaddle_d = 1;
        float rpaddle_d = -1;

        float rpaddle_v = 2.0;
        float lpaddle_v = 2.0;

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

        bool singleplayer;
        int16_t lscore = 0;
        int16_t rscore = 0;

        bool firstloop = true;
        float maxleveltime = 10; 
        float currentleveltime = 0;

        long _player1LastpaddleCount;
        RotaryEncoder *_player1paddle;

        long _player2LastpaddleCount;
        RotaryEncoder *_player2paddle;

        void midline();
        void paddle(bool player, bool leftside, float &d, int16_t x, float &y, float &y_old);
        void scores();
        void calc_target_y();
        void ball(float elapsed);

    public:
        void Setup(TFT_eSPI screen, RotaryEncoder *player1);
        void Setup(TFT_eSPI screen, RotaryEncoder *player1, RotaryEncoder *player2);
        void Loop();
};