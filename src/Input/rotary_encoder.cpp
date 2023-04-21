#include "rotary_encoder.hpp"

RotaryEncoder::RotaryEncoder(uint8_t clk_pin, uint8_t dt_pin, uint8_t switch1_pin, uint8_t switch2_pin, bool hw_pullups)
{
    _dt = dt_pin;
    _clk = clk_pin;
    _sw1 = switch1_pin;
    _sw2 = switch2_pin;

    Switch1Pressed = false;
    Switch2Pressed = false;

    uint8_t inputmode = INPUT;
    if(!hw_pullups)
      inputmode = INPUT_PULLUP;

    pinMode(_clk, inputmode);
    pinMode(_dt, inputmode);


    pinMode(_sw1, INPUT_PULLUP);
    pinMode(_sw2, INPUT_PULLUP);

    Serial.println("Rotary encoder setup done!");
}

void RotaryEncoder::Loop()
{
    // read X and Y analog values
    _currValueAB  = digitalRead(_clk) << 1;
    _currValueAB |= digitalRead(_dt);
    
    switch ((_prevValueAB | _currValueAB))
    {
                                                    //fast MCU
      //case 0b0001: case 0b1110:                                   //CW states, 1 count  per click
    case 0b0001: case 0b1110: case 0b1000: case 0b0111:         //CW states, 2 counts per click
        Counter++;
        break;                                              //fast MCU
      //case 0b0100: case 0b1011:                                   //CCW states, 1 count  per click
    case 0b0100: case 0b1011: case 0b0010: case 0b1101:         //CCW states, 2 counts per click
        Counter--;
        break;
    }

    _prevValueAB = _currValueAB << 2;

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
