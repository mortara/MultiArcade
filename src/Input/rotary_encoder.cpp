#include "rotary_encoder.h"

#define CLK_PIN  16 // ESP32 pin GIOP36 (ADC0) connected to VRX pin
#define DT_PIN  17 // ESP32 pin GIOP39 (ADC0) connected to VRY pin
#define SW_PIN   5 // ESP32 pin GIOP17 connected to SW  pin

void RotaryEncoder::Setup()
{
    pinMode(CLK_PIN, INPUT_PULLUP);

    pinMode(DT_PIN, INPUT_PULLUP);

    pinMode(SW_PIN, INPUT_PULLUP);

}

void RotaryEncoder::Loop()
{
    // read X and Y analog values
    readAB();

    SW = digitalRead(SW_PIN);
}

void RotaryEncoder::readAB()
{
  //noInterrupts();                                               //disable interrupts

    
                                                       //fast MCU
  _currValueAB  = digitalRead(CLK_PIN) << 1;
  _currValueAB |= digitalRead(DT_PIN);
  
  switch ((_prevValueAB | _currValueAB))
  {
                                                   //fast MCU
    case 0b0001: case 0b1110:                                   //CW states, 1 count  per click
  //case 0b0001: case 0b1110: case 0b1000: case 0b0111:         //CW states, 2 counts per click
      Counter++;
      break;                                              //fast MCU
    case 0b0100: case 0b1011:                                   //CCW states, 1 count  per click
  //case 0b0100: case 0b1011: case 0b0010: case 0b1101:         //CCW states, 2 counts per click
      Counter--;
      break;
  }

  _prevValueAB = _currValueAB << 2;                             //update previouse state

  //interrupts();                                                 //enable interrupts
}