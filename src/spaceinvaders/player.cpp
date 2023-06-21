#include "player.hpp"

Player::Player(RotaryEncoder *playerpaddle, TFT_eSPI* screen)
{
    _rotary = playerpaddle;
    _lastCount = _rotary->GetCounter();
    OutOfBoundsMethod = 3;
    float scale = 1;
    ObjectType = 1;
    GameObject::Setup(7, new Vector2DF[7] 
        {
            Vector2DF(0.0f,-4.0f) * scale, 
            Vector2DF(1.0f,0.0f)* scale,
            Vector2DF(4.0f,0.0f)* scale, 
            Vector2DF(4.0f,2.0f)* scale,
            Vector2DF(-4.0f,2.0f)* scale,
            Vector2DF(-4.0f,0.0f)* scale,
            Vector2DF(-1.0f,0.0f)* scale
        });

    Position = Vector2DF(screen->width() / 2.0, screen->height() - 10);
}

bool Player::Control()
{
    int paddlecounter = _rotary->GetCounter();
    int diff = paddlecounter - _lastCount;
    _lastCount = paddlecounter;

    if(diff != 0)
    {
        Position.X += diff * _speed;
    }


    if(_rotary->SW2 == 0 || _rotary->SW == 0)  // Fire
        return true;

    return false;
}