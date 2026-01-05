#include "tempest_player.hpp"
#include "../general/config.h"

TempestPlayer::TempestPlayer(RotaryEncoder *rotary)
{
    _rotary = rotary;
    _lastCount = _rotary->GetCounter();
    
    ObjectType = 9;  // 9 = Tempest Player
    OutOfBoundsMethod = 0;  // Don't use standard bounds checking
    Angle = 0.0f;  // Start at top
    
    Color = TFT_GREEN;
    Radius = 4;
    Size = Vector2DF(4, 4);
    
    // Set up player shape as a small claw/triangle
    double scale = 1.5;
    GameObject::Setup(3, new Vector2DF[3] {
        Vector2DF(0.0f, 3.0f) * scale,   // Point outward
        Vector2DF(-2.0f, -1.5f) * scale, // Left base
        Vector2DF(2.0f, -1.5f) * scale   // Right base
    });
}

void TempestPlayer::Control()
{
    int paddleCounter = _rotary->GetCounter();
    int diff = paddleCounter - _lastCount;
    _lastCount = paddleCounter;
    
    if (diff != 0)
    {
        Angle += (float)diff * _rotationSpeed;
        
        // Wrap angle to 0-360 range
        while (Angle >= 360.0f)
            Angle -= 360.0f;
        while (Angle < 0.0f)
            Angle += 360.0f;
    }
}

bool TempestPlayer::FirePressed()
{
    return (_rotary->ReadSwitch1() == 0);  // Read current state directly for continuous firing
}

bool TempestPlayer::SuperZapperPressed()
{
    return _rotary->Switch2Pressed;  // Use debounced value for one-time action
}
