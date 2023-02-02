
#include <Arduino.h>
#include <list>
#include <TFT_eSPI.h>
#include "ship.hpp"
#include "bullet.hpp"
#include "asteroid.hpp"
#include "../general/Game.hpp"
#include "../general/GameWorld.hpp"
#include "../Input/rotary_encoder.hpp"


class AsteroidsGame : public Game
{
    private:
        unsigned long _lastLoop;
        
        RotaryEncoder *_rotary;
        Ship *_ship;
        float _reloadtime = 0.3;
        float _lastshot = 0;

        GameWorld* _world;
        
        int lives = 3;
        int score = 0;
        int level = 0;
        
        float stagetimer = 0;

        void scores();
        void StartLevel(int l);
        void ProcessShip(float elapsed);
        void ProcessObjects(float elapsed);

    public:
        AsteroidsGame(TFT_eSPI* screen, RotaryEncoder *player1);

        void Loop();
};