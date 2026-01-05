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
        SemaphoreHandle_t taskMutex;
        TaskHandle_t taskHandle;

    void Setup()
    {
        Tasks = new std::list<BuzzerTask *>();
        taskMutex = xSemaphoreCreateMutex();
        taskHandle = NULL;

        pinMode(BUZZER_PIN, OUTPUT);
        
        xTaskCreatePinnedToCore(
            Task1code, /* Function to implement the task */
            "Task1", /* Name of the task */
            10000,  /* Stack size in words */
            this,  /* Task input parameter */
            0,  /* Priority of the task */
            &taskHandle,  /* Task handle. */
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
                xSemaphoreTake(l_pThis->taskMutex, portMAX_DELAY);
                BuzzerTask *bt = l_pThis->Tasks->front();
                xSemaphoreGive(l_pThis->taskMutex);
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
                xSemaphoreTake(l_pThis->taskMutex, portMAX_DELAY);
                l_pThis->Tasks->remove(bt);
                xSemaphoreGive(l_pThis->taskMutex);
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

        xSemaphoreTake(taskMutex, portMAX_DELAY);
        Tasks->push_back(bt);
        xSemaphoreGive(taskMutex);
    }

    void PlayNoise(unsigned long duration)  {

        BuzzerTask *bt = new BuzzerTask();
        bt->Type = 2;
        bt->Duration = duration;
        bt->Frequency = 0;

        xSemaphoreTake(taskMutex, portMAX_DELAY);
        Tasks->push_back(bt);
        xSemaphoreGive(taskMutex);
    }

    void StopSound()
    {
        noTone(BUZZER_PIN);
    }

};

#endif