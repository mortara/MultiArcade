#include "tempest_game.hpp"
#include "../general/config.h"
#include <math.h>

TempestGame::TempestGame(TFT_eSPI *screen, RotaryEncoder *rotary) : Game(screen)
{
    _tft = screen;
    _rotary = rotary;
    _world = new GameWorld(screen);
    _player = new TempestPlayer(_rotary);
    
    _centerPos = Vector2DF(ScreenWidth / 2, ScreenHeight / 2);
    
    Serial.println("Tempest initialized!");
}

Vector2DF TempestGame::GetPositionFromPolar(float angle, float radius)
{
    float rad = degreesToRadians(angle);
    return Vector2DF(
        _centerPos.X + cos(rad) * radius,
        _centerPos.Y + sin(rad) * radius
    );
}

void TempestGame::DrawWeb()
{
    // Draw the radial lanes
    for (int i = 0; i < NUM_LANES; i++)
    {
        float angle = (360.0f / NUM_LANES) * i;
        Vector2DF innerPos = GetPositionFromPolar(angle, CENTER_RADIUS);
        Vector2DF outerPos = GetPositionFromPolar(angle, RIM_RADIUS);
        _tft->drawLine(innerPos.X, innerPos.Y, outerPos.X, outerPos.Y, TFT_DARKGREY);
    }
    
    // Draw outer rim circle
    _tft->drawCircle(_centerPos.X, _centerPos.Y, RIM_RADIUS, TFT_DARKGREY);
    
    // Draw inner circle
    _tft->drawCircle(_centerPos.X, _centerPos.Y, CENTER_RADIUS, TFT_DARKGREY);
}

void TempestGame::UpdateScore()
{
    _tft->drawString("Lvl:" + String(level) + " Score:" + String(score) + " Lives:" + String(lives) + " SZ:" + String(superZappers), 2, 1, 1);
}

int TempestGame::CalculateMaxEnemies(int level)
{
    int maxEnemies = INITIAL_ENEMIES + (level - 1) * ENEMIES_PER_LEVEL;
    if (maxEnemies > MAX_ENEMIES)
        maxEnemies = MAX_ENEMIES;
    return maxEnemies;
}

void TempestGame::StartLevel(int l)
{
    level = l;
    superZappers = 2;  // Give 2 super zappers per level
    _enemySpawnTimer = 0;
    _enemySpawnInterval = BASE_SPAWN_INTERVAL - (level * SPAWN_DECREASE_PER_LEVEL);
    if (_enemySpawnInterval < MIN_SPAWN_INTERVAL)
        _enemySpawnInterval = MIN_SPAWN_INTERVAL;
    
    _tft->fillScreen(DEFAULT_BG_COLOR);
    DrawWeb();
    
    _player->Angle = 0.0f;
    _world->Clear();
    
    // Spawn initial enemies
    int numEnemies = CalculateMaxEnemies(level);
        
    for (int i = 0; i < numEnemies; i++)
    {
        SpawnEnemy();
    }
    
    Serial.println("Level " + String(level) + " started with " + String(numEnemies) + " enemies");
}

void TempestGame::SpawnEnemy()
{
    // Pick a random lane
    int lane = random(NUM_LANES);
    float angle = (360.0f / NUM_LANES) * lane;
    
    TempestEnemy *enemy = new TempestEnemy(angle, level);
    _world->AddObject(enemy);
}

void TempestGame::UpdateObjectPositions()
{
    std::list<GameObject *> *objects = _world->GetObjects();
    
    for (GameObject *obj : *objects)
    {
        if (obj->ObjectType == 7)  // Bullet
        {
            TempestBullet *bullet = static_cast<TempestBullet *>(obj);
            obj->Position = GetPositionFromPolar(bullet->Angle, bullet->RadialDistance);
        }
        else if (obj->ObjectType == 8)  // Enemy
        {
            TempestEnemy *enemy = static_cast<TempestEnemy *>(obj);
            obj->Position = GetPositionFromPolar(enemy->Angle, enemy->RadialDistance);
        }
    }
    
    // Update player position
    _player->Position = GetPositionFromPolar(_player->Angle, RIM_RADIUS);
    _player->SetOrientation(_player->Angle - 90.0f);  // Point inward
}

void TempestGame::ProcessPlayer(float elapsed)
{
    _player->Control();
    
    // Check for shooting
    if (_player->FirePressed() && _lastShot >= _reloadTime)
    {
        TempestBullet *bullet = new TempestBullet(_player->Angle, RIM_RADIUS - 5.0f);
        _world->AddObject(bullet);
        _lastShot = 0;
        _buzz->PlayTone(150, 50);
    }
    
    // Check for super zapper
    if (_player->SuperZapperPressed() && superZappers > 0)
    {
        superZappers--;
        _buzz->PlayTone(200, 200);
        
        // Destroy all enemies
        std::list<GameObject *> *objects = _world->GetObjects();
        for (GameObject *obj : *objects)
        {
            if (obj->ObjectType == 8)  // Enemy
            {
                obj->Delete = true;
                score += 25;
            }
        }
        
        Serial.println("Super Zapper used! " + String(superZappers) + " remaining");
    }
}

void TempestGame::ProcessBullets(float elapsed)
{
    std::list<GameObject *> *objects = _world->GetObjects();
    
    for (GameObject *obj : *objects)
    {
        if (obj->ObjectType == 7 && !obj->Delete)  // Bullet
        {
            TempestBullet *bullet = static_cast<TempestBullet *>(obj);
            
            // Move bullet inward
            bullet->RadialDistance -= 100.0f * elapsed;
            
            // Delete if reached center
            if (bullet->RadialDistance < CENTER_RADIUS)
            {
                bullet->Delete = true;
            }
            
            // Check collision with enemies
            for (GameObject *other : *objects)
            {
                if (other->ObjectType == 8 && !other->Delete)  // Enemy
                {
                    TempestEnemy *enemy = static_cast<TempestEnemy *>(other);
                    
                    // Check if they're in the same lane and close enough
                    float angleDiff = fabs(bullet->Angle - enemy->Angle);
                    if (angleDiff > 180.0f)
                        angleDiff = 360.0f - angleDiff;
                    
                    if (angleDiff < (360.0f / NUM_LANES / 2.0f))  // Same lane
                    {
                        float radiusDiff = fabs(bullet->RadialDistance - enemy->RadialDistance);
                        if (radiusDiff < COLLISION_DISTANCE)  // Close enough
                        {
                            bullet->Delete = true;
                            enemy->Delete = true;
                            score += 50 * level;
                            _buzz->PlayTone(300, 100);
                            break;
                        }
                    }
                }
            }
        }
    }
}

void TempestGame::ProcessEnemies(float elapsed)
{
    std::list<GameObject *> *objects = _world->GetObjects();
    
    for (GameObject *obj : *objects)
    {
        if (obj->ObjectType == 8 && !obj->Delete)  // Enemy
        {
            TempestEnemy *enemy = static_cast<TempestEnemy *>(obj);
            
            // Move enemy outward using its calculated speed
            enemy->RadialDistance += enemy->Speed * elapsed;
            
            // Check if enemy reached the rim (player position)
            if (enemy->RadialDistance >= RIM_RADIUS - 2.0f)
            {
                // Check if it hits the player
                float angleDiff = fabs(enemy->Angle - _player->Angle);
                if (angleDiff > 180.0f)
                    angleDiff = 360.0f - angleDiff;
                
                if (angleDiff < (360.0f / NUM_LANES))  // Player in this lane
                {
                    // Player hit!
                    enemy->Delete = true;
                    lives--;
                    _buzz->PlayNoise(400);
                    
                    Serial.println("Player hit! Lives remaining: " + String(lives));
                    
                    if (lives <= 0)
                    {
                        GameStage = 2;  // Game over
                        return;
                    }
                    else
                    {
                        _stageTimer = 2;
                        GameStage = 3;  // Respawn stage
                        return;
                    }
                }
                else
                {
                    // Enemy missed, delete it
                    enemy->Delete = true;
                }
            }
        }
    }
    
    // Spawn new enemies periodically
    _enemySpawnTimer += elapsed;
    if (_enemySpawnTimer >= _enemySpawnInterval)
    {
        _enemySpawnTimer = 0;
        int currentEnemies = _world->CountObjects(8);
        int maxEnemies = CalculateMaxEnemies(level);
            
        if (currentEnemies < maxEnemies)
        {
            SpawnEnemy();
        }
    }
}

void TempestGame::Loop()
{
    unsigned long time = millis();
    float elapsed = (float)(time - _lastLoop) / 1000.0f;
    _lastShot += elapsed;
    
    if (GameStage == 0)  // Menu
    {
        _tft->drawString("TEMPEST", ScreenWidth / 2 - 30, ScreenHeight / 2 - 10, 2);
        _tft->drawString("Press to Start", ScreenWidth / 2 - 35, ScreenHeight / 2 + 10, 1);
        
        if (_rotary->Switch1Pressed || _rotary->Switch2Pressed)
        {
            _tft->fillScreen(DEFAULT_BG_COLOR);
            score = 0;
            lives = 3;
            GameStage = 1;
            StartLevel(1);
            delay(300);
        }
    }
    else if (GameStage == 1)  // Playing
    {
        ProcessPlayer(elapsed);
        ProcessBullets(elapsed);
        ProcessEnemies(elapsed);
        
        // Clean up deleted objects
        _world->Cleanup();
        
        // Update all positions based on polar coordinates
        UpdateObjectPositions();
        
        // Render everything
        _player->Render(_tft);
        _world->RenderObjects();
        
        // Redraw web periodically to keep it visible
        static float webRedrawTimer = 0;
        webRedrawTimer += elapsed;
        if (webRedrawTimer > 1.0f)
        {
            DrawWeb();
            webRedrawTimer = 0;
        }
        
        UpdateScore();
        
        // Check for level complete
        int enemiesLeft = _world->CountObjects(8);
        if (enemiesLeft == 0 && _enemySpawnTimer > 3.0f)  // No enemies and no recent spawns
        {
            score += 500 * level;
            Serial.println("Level complete! Score: " + String(score));
            delay(1000);
            StartLevel(level + 1);
        }
    }
    else if (GameStage == 3)  // Respawn
    {
        ProcessBullets(elapsed);
        ProcessEnemies(elapsed);
        _world->Cleanup();
        UpdateObjectPositions();
        _world->RenderObjects();
        
        DrawWeb();
        UpdateScore();
        
        _stageTimer -= elapsed;
        _tft->drawString("Get Ready!", ScreenWidth / 2 - 30, ScreenHeight / 2 - 10, 1);
        
        if (_stageTimer <= 0)
        {
            GameStage = 1;
        }
    }
    else if (GameStage == 2)  // Game Over
    {
        _world->Cleanup();
        UpdateObjectPositions();
        _world->RenderObjects();
        
        DrawWeb();
        UpdateScore();
        _tft->drawString("GAME OVER", ScreenWidth / 2 - 30, ScreenHeight / 2 - 10, 2);
        _tft->drawString("Press to Restart", ScreenWidth / 2 - 35, ScreenHeight / 2 + 10, 1);
        
        if (_rotary->Switch1Pressed || _rotary->Switch2Pressed)
        {
            _tft->fillScreen(DEFAULT_BG_COLOR);
            delay(300);
            GameStage = 0;
        }
    }
    
    _lastLoop = time;
}
