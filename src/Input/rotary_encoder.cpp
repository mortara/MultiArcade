#include "rotary_encoder.hpp"

RotaryEncoder::RotaryEncoder(uint8_t clk_pin, uint8_t dt_pin, uint8_t switch1_pin, uint8_t switch2_pin, bool hw_pullups)
{
    _sw1 = switch1_pin;
    _sw2 = switch2_pin;

    Switch1Pressed = false;
    Switch2Pressed = false;

    uint8_t inputmode = INPUT;
    if(!hw_pullups)
      inputmode = INPUT_PULLUP;

    encoder.attachHalfQuad(clk_pin, dt_pin);
    encoder.setCount(0);


    pinMode(_sw1, INPUT_PULLUP);
    pinMode(_sw2, INPUT_PULLUP);

    _lastRead = millis();

    Serial.println("Rotary encoder setup done!");
}

int64_t RotaryEncoder::GetCounter()
{
    return encoder.getCount();
}

int RotaryEncoder::ReadSwitch1()
{
    return digitalRead(_sw1);
}

void RotaryEncoder::Loop()
{
    unsigned long now = millis();
    if(now - _lastRead < 100)
      return;
    _lastRead = now;

    SW = digitalRead(_sw1);
    if(SW == 0 && SW_OLD != 0)
      Switch1Pressed = true;
    else
      Switch1Pressed = false;

    SW_OLD = SW;

    SW2 = digitalRead(_sw2);
    if(SW2 == 0 && SW2_OLD != 0)
      Switch2Pressed = true;
    else
      Switch2Pressed = false;

    SW2_OLD = SW2;

}
