#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>

#define BLACK 0x0000
#define WHITE 0xFFFF
#define GREY  0x5AEB

class Screen
{
    public:

        int16_t Width;
        int16_t Height;

        void Setup();

        void Clear(u_int32_t color);

    private:

        TFT_eSPI tft;
};