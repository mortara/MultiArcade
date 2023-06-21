#include <Arduino.h>
#include <list>
#include "../general/config.h"

#ifndef SOUND_H
#define SOUND_H

struct BuzzerTask
{
    int Type;
    unsigned int Frequency;
    unsigned long Duration;
};

class Buzzer
{
    public:
        std::list<BuzzerTask *>* Tasks;
        volatile bool lock;

    void Setup()
    {
        Tasks = new std::list<BuzzerTask *>();
        TaskHandle_t xHandle = NULL;

        pinMode(BUZZER_PIN, OUTPUT);
        
        xTaskCreatePinnedToCore(
            Task1code, /* Function to implement the task */
            "Task1", /* Name of the task */
            10000,  /* Stack size in words */
            this,  /* Task input parameter */
            0,  /* Priority of the task */
            &xHandle,  /* Task handle. */
            0); /* Core where the task should run */
    }

    static void Task1code(void *pvParameters) {
        Buzzer *l_pThis = static_cast<Buzzer *>(pvParameters);
        
        for(;;) {
            if(l_pThis->Tasks->empty())
            {
                noTone(BUZZER_PIN);
                delay(10);
            }
            else
            {
                while(l_pThis->lock)
                    delay(1);

                l_pThis->lock = true;
                BuzzerTask *bt = l_pThis->Tasks->front();
                l_pThis->lock = false;
                switch(bt->Type)
                {
                    case 1:
                        tone(BUZZER_PIN, bt->Frequency, bt->Duration);
                        break;
                    case 2:
                        unsigned long time = millis();
                        while(millis() - time <= bt->Duration)  {  
                            int dur = random(3) + 3;
                            tone(BUZZER_PIN, random(100, 300));   // change the parameters of random() for different sound
                            delay(dur);
                        }     
                        noTone(BUZZER_PIN);
                }
                l_pThis->lock = true;
                l_pThis->Tasks->remove(bt);
                l_pThis->lock = false;
                delete bt;
            }
        }
    }

    void PlayTone(unsigned int frequency, unsigned long duration)
    {
        BuzzerTask *bt = new BuzzerTask();
        bt->Type = 1;
        bt->Duration = duration;
        bt->Frequency = frequency;

        while(lock)
            delay(5);

        lock = true;
        Tasks->push_back(bt);
        lock = false;
    }

    void PlayNoise(unsigned long duration)  {

        BuzzerTask *bt = new BuzzerTask();
        bt->Type = 2;
        bt->Duration = duration;
        bt->Frequency = 0;

        while(lock)
            delay(1);

        lock = true;
        Tasks->push_back(bt);
        lock = false;
    }

    void StopSound()
    {
        noTone(BUZZER_PIN);
    }

};

#endif