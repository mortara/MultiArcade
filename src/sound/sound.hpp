#include <Arduino.h>

#ifndef SOUND_H
#define SOUND_H

#define BUZZER_PIN 22


class Buzzer
{
    public:

    void Setup()
    {
        pinMode(BUZZER_PIN, OUTPUT);
    }

    void PlayTone(unsigned int frequency, unsigned long duration)
    {
        tone(BUZZER_PIN, frequency, duration);

        noTone(BUZZER_PIN);
    }

    void PlayNoise(unsigned long duration)  {
        unsigned long time = millis();
        while(millis() - time <= duration)  {  // change "500" for different durations in ms.
            tone(BUZZER_PIN, random(50, 300));   // change the parameters of random() for different sound
        }

        noTone(BUZZER_PIN);
    }

};

#endif