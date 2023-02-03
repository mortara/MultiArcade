
#ifndef CONFIGFILE_H

    #define degreesToRadians(angleDegrees) ((angleDegrees) * M_PI / 180.0)
    #define radiansToDegrees(angleRadians) ((angleRadians) * 180.0 / M_PI)

    #define DEFAULT_TEXT_COLOR TFT_WHITE
    #define DEFAULT_TEXT2_COLOR TFT_BLUE
    #define DEFAULT_BG_COLOR TFT_BLACK
    #define DEFAULT_FG_COLOR TFT_WHITE

    #define BLACK 0x0000
    #define WHITE 0xFFFF
    #define GREY 0x5AEB

    // Piezo buzzer
    #define BUZZER_PIN 22
    
    // Player 1 paddle
    #define CLK1_PIN 17 
    #define DT1_PIN 16
    #define SW1_PIN 5 
    #define SW1_PIN2 21

    // Player 2 paddle
    #define CLK2_PIN 25 
    #define DT2_PIN 26
    #define SW2_PIN 27 
    #define SW2_PIN2 14

    #define CONFIGFILE_H
    
#endif