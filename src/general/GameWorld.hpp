#include <Arduino.h>
#include <list>
#include "gameobject.hpp"
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
        void DeleteObjects();
        int CountObjects(int type);
        std::list<GameObject *>* GetObjects();

        GameObject* CollisionCheck(GameObject *go, int objecttype);

    private:
        std::list<GameObject *>* _objects;
        TFT_eSPI* _tft;
        
};

#endif