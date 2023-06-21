#include <Arduino.h>
#include <list>
#include "gameobject.hpp"
#include "debris.hpp"
#include <TFT_eSPI.h>

#ifndef GAMEWORLD_H
#define GAMEWORLD_H

class GameWorld
{
    public:

        GameWorld(TFT_eSPI* tft);

        bool AddObject(GameObject *obj);
        bool RemoveObject(GameObject *obj);

        void Loop(float elapsed);
        void MoveObjects(float elapsed);
        void RenderObjects();
        void Clear();
        void Cleanup();
        int CountObjects(int type);
        std::list<GameObject *>* GetObjects();

        GameObject* CollisionCheck(GameObject *go, int objecttype);
        void Explode(GameObject *go);

        int Width = 0;
        int Height = 0;
        bool _gravityenabled = false;
        void SetGravity(Vector2DF grav);

    private:
        std::list<GameObject *>* _objects;
        TFT_eSPI* _tft;
        Vector2DF _gravity = Vector2DF(0,0);

        unsigned long _lastCleanup;
};

#endif