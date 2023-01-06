#include <Arduino.h>

#ifndef ROTARYENCODER_H
#define ROTARYENCODER_H

class RotaryEncoder
{
    public:
        void Setup();
        void Loop();
        
        int Counter = 0;
        int SW = 0;

    private:
        void readAB();

        volatile uint8_t _prevValueAB = 0;    //previouse state of "A"+"B"
        volatile uint8_t _currValueAB = 0;    //current   state of "A"+"B"
};

#endif