#include <Arduino.h>
#include <ESP32Encoder.h>

#ifndef ROTARYENCODER_H
#define ROTARYENCODER_H

class RotaryEncoder
{
    public:
        RotaryEncoder(uint8_t clk_pin, uint8_t dt_pin, uint8_t switch1_pin, uint8_t switch2_pin, bool hw_pullups);
        void Loop();

        int SW = 0;
        int SW2 = 0;
        bool Switch1Pressed = false; // Debounced
        bool Switch2Pressed = false;

        int64_t GetCounter();

    private:
    
        ESP32Encoder encoder;

        uint8_t _sw1;
        uint8_t _sw2;

        int SW_OLD = 0;
        int SW2_OLD = 0;

        unsigned long _lastRead;
};

#endif
