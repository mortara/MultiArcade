#include <Arduino.h>

#ifndef ROTARYENCODER_H
#define ROTARYENCODER_H

class RotaryEncoder
{
    public:
        void Setup(uint8_t clk_pin, uint8_t dt_pin, uint8_t switch1_pin, uint8_t switch2_pin, bool hw_pullups);
        void Loop();
        
        int Counter = 0;
        
        int SW = 0;
        int SW2 = 0;
        bool Switch1Pressed; // Debounced
        bool Switch2Pressed;

    private:
    
        uint8_t _clk;
        uint8_t _dt;
        uint8_t _sw1;
        uint8_t _sw2;


        
        int SW_OLD = 0;
        int SW2_OLD = 0;

        volatile uint8_t _prevValueAB = 0;    //previouse state of "A"+"B"
        volatile uint8_t _currValueAB = 0;    //current   state of "A"+"B"
};

#endif