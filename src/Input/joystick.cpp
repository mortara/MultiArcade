#include "joystick.h"

#define VRX_PIN  26 // ESP32 pin GIOP36 (ADC0) connected to VRX pin
#define VRY_PIN  25 // ESP32 pin GIOP39 (ADC0) connected to VRY pin
#define SW_PIN   35 // ESP32 pin GIOP17 connected to SW  pin

void Joystick::Setup()
{
    pinMode(VRX_PIN, INPUT);

    pinMode(VRY_PIN, INPUT);

    pinMode(SW_PIN, INPUT_PULLUP);

}

void Joystick::Loop()
{
    // read X and Y analog values
    X = analogRead(VRX_PIN);
    Y = analogRead(VRY_PIN);

    SW = digitalRead(SW_PIN);
}