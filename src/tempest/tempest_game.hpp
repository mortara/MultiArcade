#ifndef TEMPEST_GAME_H
#define TEMPEST_GAME_H

#include <Arduino.h>
#include <list>
#include <TFT_eSPI.h>
#include "tempest_player.hpp"
#include "tempest_bullet.hpp"
#include "tempest_enemy.hpp"
#include "../general/Game.hpp"
#include "../general/GameWorld.hpp"
#include "../Input/rotary_encoder.hpp"

class TempestGame : public Game
{
    private:
        RotaryEncoder *_rotary;
        TempestPlayer *_player;
        GameWorld *_world;
        
        int lives = 3;
        int score = 0;
        int level = 0;
        int superZappers = 0;
        
        float _reloadTime = 0.2f;
        float _lastShot = 0;
        float _stageTimer = 0;
        float _enemySpawnTimer = 0;
        float _enemySpawnInterval = 2.0f;
        
        const int NUM_LANES = 16;
        const float RIM_RADIUS = 55.0f;
        const float CENTER_RADIUS = 5.0f;
        
        static constexpr float BASE_SPAWN_INTERVAL = 2.0f;
        static constexpr float SPAWN_DECREASE_PER_LEVEL = 0.1f;
        static constexpr float MIN_SPAWN_INTERVAL = 0.5f;
        
        Vector2DF _centerPos;
        
        void DrawWeb();
        void UpdateScore();
        void StartLevel(int l);
        void ProcessPlayer(float elapsed);
        void ProcessBullets(float elapsed);
        void ProcessEnemies(float elapsed);
        void SpawnEnemy();
        void UpdateObjectPositions();
        Vector2DF GetPositionFromPolar(float angle, float radius);
        
    public:
        TempestGame(TFT_eSPI *screen, RotaryEncoder *rotary);
        void Loop();
};

#endif
