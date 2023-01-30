#include <Arduino.h>
#include <list>

#ifndef SOUND_H
#define SOUND_H

#define BUZZER_PIN 22

class BuzzerTask
{
    public:
        int Type;
        unsigned int Frequency;
        unsigned long Duration;
};

class Buzzer
{
    private:
        TaskHandle_t Task1;
        

    public:
        std::list<BuzzerTask *> Tasks;

    void Setup()
    {
        pinMode(BUZZER_PIN, OUTPUT);

        xTaskCreatePinnedToCore(
            Task1code, /* Function to implement the task */
            "Task1", /* Name of the task */
            10000,  /* Stack size in words */
            this,  /* Task input parameter */
            0,  /* Priority of the task */
            &Task1,  /* Task handle. */
            0); /* Core where the task should run */
    }

    static void Task1code(void *pvParameters) {
        Buzzer *l_pThis = (Buzzer *) pvParameters;
        
        for(;;) {
            if(l_pThis->Tasks.empty())
            {
                noTone(BUZZER_PIN);
                delay(100);
            }
            else
            {
                BuzzerTask *bt = l_pThis->Tasks.front();
                switch(bt->Type)
                {
                    case 1:
                        tone(BUZZER_PIN, bt->Frequency, bt->Duration);
                        break;
                    case 2:
                        unsigned long time = millis();
                        while(millis() - time <= bt->Duration)  {  
                            tone(BUZZER_PIN, random(100, 300), random(5));   // change the parameters of random() for different sound
                        }
                }
                l_pThis->Tasks.pop_front();
            }
            delay(50);
        }
    }

    void PlayTone(unsigned int frequency, unsigned long duration)
    {
        BuzzerTask *bt = new BuzzerTask();
        bt->Type = 1;
        bt->Duration = duration;
        bt->Frequency = frequency;

        Tasks.push_back(bt);
    }

    void PlayNoise(unsigned long duration)  {

        BuzzerTask *bt = new BuzzerTask();
        bt->Type = 2;
        bt->Duration = duration;
        bt->Frequency = 0;

        Tasks.push_back(bt);
    }

    void StopSound()
    {
        noTone(BUZZER_PIN);
    }

};

#endif