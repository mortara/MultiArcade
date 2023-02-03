#include <Arduino.h>
#include <list>
#include <TFT_eSPI.h>
#include "../general/Game.hpp"
#include "../general/GameWorld.hpp"
#include "../Input/rotary_encoder.hpp"
#include "player.hpp"
#include "alien.hpp"
#include "beam.hpp"

class SpaceInvadersGame : public Game
{
    private:
        RotaryEncoder *_rotary;

        Player *_ship;
        float _reloadtime = 0.5;
        float _lastshot = 0;
        float _lastalienshot = 0;

        GameWorld* _world;
        
        void ProcessShip(float elapsed);
        void ProcessObjects(float elapsed);

        int lives = 0;
        int score = 0;
        int level = 0;
        
        float stagetimer = 0;
        int _maxcols = 8;
        int _maxrows = 6;
        void scores();
        void StartLevel(int l);
    public:
        SpaceInvadersGame(TFT_eSPI* screen, RotaryEncoder *player1); 
        void Loop();
};