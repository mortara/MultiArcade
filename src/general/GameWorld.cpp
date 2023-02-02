#include "GameWorld.hpp"


GameWorld::GameWorld(TFT_eSPI* tft)
{
    _tft = tft;
    _objects = new std::list<GameObject *>();
}

bool GameWorld::AddObject(GameObject *go)
{
    _objects->push_back(go);
    return true;
}

bool GameWorld::RemoveObject(GameObject *go)
{
    _objects->remove(go);
    return true;
}

void GameWorld::Loop(float elapsed)
{
    MoveObjects(elapsed);
    DeleteObjects();
    RenderObjects();
}

void GameWorld::MoveObjects(float elapsed)
{
    for (GameObject *obj : *_objects)
    {
        if(obj->Delete == true)
            continue;

        obj->Move(elapsed);
             
        if(obj->OutOfBoundsCheck(_tft))
        {
            obj->Delete = true;
            continue;
        }
    }
}

void GameWorld::RenderObjects()
{
    for (GameObject *obj : *_objects)
    {
        if(obj->Delete == true)
            continue;

        obj->Render(_tft); 
    }
}

void GameWorld::DeleteObjects()
{
    std::list<GameObject *> _removedobjects;
    for (GameObject *obj : *_objects)
    {
        if(obj->Delete == true)
            _removedobjects.push_back(obj);
    }

    for (GameObject *obj : _removedobjects)
    {
        obj->RemoveFromScreen(_tft);
        _objects->remove(obj);
        delete obj;
    }
}

std::list<GameObject *>* GameWorld::GetObjects()
{
    return _objects;
}

int GameWorld::CountObjects(int type)
{
    return std::count_if(_objects->begin(), _objects->end(), [&](GameObject *go) { return go->ObjectType == type; });
}

GameObject* GameWorld::CollisionCheck(GameObject *go, int objecttype)
{
    for (GameObject *obj : *_objects)
    {
        if(obj->Delete || obj->ObjectType != objecttype)
            continue;

        if(go->CollidesWith(obj))
            return obj;
    }

    return NULL;
}